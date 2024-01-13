//--STRIP
#ifndef PAGED_ALLOCATOR_H
#define PAGED_ALLOCATOR_H
//--STRIP

/*************************************************************************/
/*  paged_allocator.h                                                    */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/memory.h"
#include "spin_lock.h"
#include "core/typedefs.h"
//--STRIP

template <class T, bool thread_safe = false>
class PagedAllocator {
	T **page_pool = nullptr;
	T ***available_pool = nullptr;
	uint32_t pages_allocated = 0;
	uint32_t allocs_available = 0;

	uint32_t page_shift = 0;
	uint32_t page_mask = 0;
	uint32_t page_size = 0;
	SpinLock spin_lock;

public:
	T *alloc() {
		if (thread_safe) {
			spin_lock.lock();
		}
		if (unlikely(allocs_available == 0)) {
			uint32_t pages_used = pages_allocated;

			pages_allocated++;
			page_pool = (T **)memrealloc(page_pool, sizeof(T *) * pages_allocated);
			available_pool = (T ***)memrealloc(available_pool, sizeof(T **) * pages_allocated);

			page_pool[pages_used] = (T *)memalloc(sizeof(T) * page_size);
			available_pool[pages_used] = (T **)memalloc(sizeof(T *) * page_size);

			for (uint32_t i = 0; i < page_size; i++) {
				available_pool[0][i] = &page_pool[pages_used][i];
			}
			allocs_available += page_size;
		}

		allocs_available--;
		T *alloc = available_pool[allocs_available >> page_shift][allocs_available & page_mask];
		if (thread_safe) {
			spin_lock.unlock();
		}
		memnew_placement(alloc, T);
		return alloc;
	}

	void free(T *p_mem) {
		if (thread_safe) {
			spin_lock.lock();
		}
		p_mem->~T();
		available_pool[allocs_available >> page_shift][allocs_available & page_mask] = p_mem;
		if (thread_safe) {
			spin_lock.unlock();
		}
		allocs_available++;
	}

	void reset(bool p_allow_unfreed = false) {
		if (!p_allow_unfreed || !HAS_TRIVIAL_DESTRUCTOR(T)) {
			ERR_FAIL_COND(allocs_available < pages_allocated * page_size);
		}
		if (pages_allocated) {
			for (uint32_t i = 0; i < pages_allocated; i++) {
				memfree(page_pool[i]);
				memfree(available_pool[i]);
			}
			memfree(page_pool);
			memfree(available_pool);
			page_pool = nullptr;
			available_pool = nullptr;
			pages_allocated = 0;
			allocs_available = 0;
		}
	}
	bool is_configured() const {
		return page_size > 0;
	}

	void configure(uint32_t p_page_size) {
		ERR_FAIL_COND(page_pool != nullptr); //sanity check
		ERR_FAIL_COND(p_page_size == 0);
		page_size = nearest_power_of_2_templated(p_page_size);
		page_mask = page_size - 1;
		page_shift = get_shift_from_power_of_2(page_size);
	}

	// Power of 2 recommended because of alignment with OS page sizes.
	// Even if element is bigger, its still a multiple and get rounded amount of pages
	PagedAllocator(uint32_t p_page_size = 4096) {
		configure(p_page_size);
	}

	~PagedAllocator() {
		ERR_FAIL_COND_MSG(allocs_available < pages_allocated * page_size, "Pages in use exist at exit in PagedAllocator");
		reset();
	}
};

//--STRIP
#endif // PAGED_ALLOCATOR_H
//--STRIP
