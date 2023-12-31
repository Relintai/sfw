/*************************************************************************/
/*  ref_ptr.cpp                                                          */
/*************************************************************************/
/*                         This file is part of:                         */
/*                          PANDEMONIUM ENGINE                           */
/*             https://github.com/Relintai/pandemonium_engine            */
/*************************************************************************/
/* Copyright (c) 2022-present Péter Magyar.                              */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "ref_ptr.h"

#include "object/reference.h"
#include "object/resource.h"

void RefPtr::operator=(const RefPtr &p_other) {
	Ref<Reference> *ref = reinterpret_cast<Ref<Reference> *>(&data[0]);
	Ref<Reference> *ref_other = reinterpret_cast<Ref<Reference> *>(const_cast<char *>(&p_other.data[0]));

	*ref = *ref_other;
}

bool RefPtr::operator==(const RefPtr &p_other) const {
	Ref<Reference> *ref = reinterpret_cast<Ref<Reference> *>(&data[0]);
	Ref<Reference> *ref_other = reinterpret_cast<Ref<Reference> *>(const_cast<char *>(&p_other.data[0]));

	return *ref == *ref_other;
}

bool RefPtr::operator!=(const RefPtr &p_other) const {
	Ref<Reference> *ref = reinterpret_cast<Ref<Reference> *>(&data[0]);
	Ref<Reference> *ref_other = reinterpret_cast<Ref<Reference> *>(const_cast<char *>(&p_other.data[0]));

	return *ref != *ref_other;
}

RefPtr::RefPtr(const RefPtr &p_other) {
	memnew_placement(&data[0], Ref<Reference>);

	Ref<Reference> *ref = reinterpret_cast<Ref<Reference> *>(&data[0]);
	Ref<Reference> *ref_other = reinterpret_cast<Ref<Reference> *>(const_cast<char *>(&p_other.data[0]));

	*ref = *ref_other;
}

bool RefPtr::is_null() const {
	Ref<Reference> *ref = reinterpret_cast<Ref<Reference> *>(&data[0]);
	return ref->is_null();
}

void RefPtr::unref() {
	Ref<Reference> *ref = reinterpret_cast<Ref<Reference> *>(&data[0]);
	ref->unref();
}

RefPtr::RefPtr() {
	ERR_FAIL_COND(sizeof(Ref<Reference>) > DATASIZE);
	memnew_placement(&data[0], Ref<Reference>);
}

RefPtr::~RefPtr() {
	Ref<Reference> *ref = reinterpret_cast<Ref<Reference> *>(&data[0]);
	ref->~Ref<Reference>();
}
