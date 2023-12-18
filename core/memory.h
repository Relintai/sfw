#ifndef MEMORY_H
#define MEMORY_H

//Simple memnew and memdelete macros so stuff that I took from the godotengine can use it.
//Not yet sure whether to use their allocator or not.
//This will be here until I decide.

#define memnew(m_class) new m_class
#define memdelete(instance) delete instance
#define memnew_arr(m_class, size) new m_class[size]
#define memdelete_arr(instance) delete[] instance

#endif

