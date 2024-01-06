
#include "sfw.h"

void print_list(const List<String> &list) {
	for (const List<String>::Element *E = list.front(); E; E = E->next()) {
		ERR_PRINT(E->get());
	}
}

void print_class_index_keys(const HashMap<String, String> &class_index) {
	for (const HashMap<String, String>::Element *E = class_index.front(); E; E = E->next) {
		ERR_PRINT(E->key());
	}
}

String get_structure_name(const String &data) {
	String fl = data.get_slicec('{', 0);
	String l = fl.get_slicec('\n', fl.get_slice_count("\n") - 1);

	l = l.get_slicec(':', 0);
	l = l.replace("struct", "").replace("class", "").replace("enum", "").replace("union", "").strip_edges();

	return l;
}

String get_structure_parents(const String &data) {
	String fl = data.get_slicec('{', 0);
	String l = fl.get_slicec('\n', fl.get_slice_count("\n") - 1);

	if (!l.contains(":")) {
		return String();
	}

	l = l.get_slicec(':', 1);

	//l = l.replace("public", "").replace("protected", "").replace("private", "");
	l = l.strip_edges();

	return l;
}

bool is_structure_template_specialization_or_parent_is_template(const String &data) {
	String fl = data.get_slicec('\n', 0);

	if (fl.contains("<")) {
		return true;
	}

	return get_structure_parents(data).contains("<");
}

String generate_section_class_list(const List<String> &list, const String &cls_prefix, const HashSet<String> &used_keywords) {
	FileAccess f;
	String code_template = f.read_file("code_remaining_template.md.html");
	String d;

	for (const List<String>::Element *E = list.front(); E; E = E->next()) {
		String c = E->get();

		String sname = get_structure_name(c);

		if (sname.empty()) {
			//ERR_PRINT(sname);
			continue;
		}

		if (used_keywords.has(cls_prefix + sname)) {
			continue;
		}

		d += code_template.replace("$CODE$", c).replace("$NAME$", sname);
	}

	return d;
}

void generate_class_index(const List<String> &list, const String &cls_prefix, HashMap<String, String> *cls_index) {
	ERR_FAIL_COND(!cls_index);

	for (const List<String>::Element *E = list.front(); E; E = E->next()) {
		String c = E->get();

		String sname = get_structure_name(c);

		if (sname.empty()) {
			//ERR_PRINT(sname);
			continue;
		}

		(*cls_index)[cls_prefix + sname] = c;
	}
}

List<String> get_template_keywords(const String &tmpl) {
	List<String> ret;

	//awful, but oh well
	Vector<String> sp = tmpl.split("|||");

	ERR_FAIL_COND_V_MSG(sp.size() % 2 == 0, ret, "Template has unterminated keywords!");

	for (int i = 1; i < sp.size(); i += 2) {
		ret.push_back(sp[i]);
	}

	return ret;
}

List<String> process_classes_and_structs(const List<String> &list) {
	List<String> ret;

	for (const List<String>::Element *E = list.front(); E; E = E->next()) {
		String s = E->get();

		s = s.replace(" _FORCE_INLINE_ ", " ");
		s = s.replace("_FORCE_INLINE_ ", "");
		s = s.replace(" _NO_DISCARD_CLASS_ ", " ");
		s = s.replace(" inline ", " ");
		s = s.replace("inline ", "");

		Vector<String> lines = s.split("\n");

		if (lines.size() == 0) {
			continue;
		}

		if (lines.size() == 1) {
			ret.push_back(s);
			continue;
		}

		String stripped;

		//remove method implementations
		int current_scope_count = 0;
		int current_target_scope_count = -1;
		int current_parenthesis_scope_count = 0;
		bool in_method = false;
		bool method_signature_found = false;
		bool in_enum = false;
		int enum_scope_start = 0;
		String processed_line;
		for (int i = 0; i < lines.size(); ++i) {
			String l = lines[i];

			if (l.contains("enum ")) {
				in_enum = true;
				enum_scope_start = current_scope_count;
			}

			for (int j = 0; j < l.length(); ++j) {
				CharType current_char = l[j];

				if (current_char == '{') {
					++current_scope_count;
				} else if (current_char == '}') {
					--current_scope_count;

					if (in_enum) {
						if (enum_scope_start == current_scope_count) {
							in_enum = false;
						}

						continue;
					}

					if (in_method) {
						if (current_target_scope_count == current_scope_count) {
							//found method end

							in_method = false;

							processed_line += ";";
						}
					}
				}

				if (in_enum) {
					continue;
				}

				if (method_signature_found) {
					if (current_char == '(') {
						++current_parenthesis_scope_count;
						continue;
					} else if (current_char == ')') {
						if (current_parenthesis_scope_count > 1) {
							--current_parenthesis_scope_count;
							continue;
						} else {
							method_signature_found = false;
							in_method = true;

							processed_line += l.substr_index(0, j + 1);
						}
					} else {
						continue;
					}
				}

				if (!in_method) {
					if (current_char == '(') {
						current_parenthesis_scope_count = 1;
						method_signature_found = true;
						current_target_scope_count = current_scope_count;
					}
				}

				if (in_method) {
					if (current_char == ';') {
						if (current_target_scope_count == current_scope_count) {
							//No implementation
							in_method = false;

							processed_line += ";";
						}
					}
				}
			}

			if (!in_method) {
				if (processed_line.size() != 0) {
					stripped += processed_line + "\n";
					processed_line.clear();
				} else {
					stripped += l + "\n";
				}
			}
		}

		ret.push_back(stripped.strip_edges());
	}

	return ret;
}

void process_file(const String &path) {
	FileAccess f;

	String file_data = f.read_file(path);

	LOG_MSG("Processing file: " + path);

	file_data = file_data.replace("\r", "");

	// Strip comments probably in probably the worst (but simplest) way possible
	List<String> file_lines_no_comments;
	Vector<String> fl = file_data.split("\n");

	file_data.clear();

	bool in_multiline_comment = false;
	bool in_comment = false;
	for (int i = 0; i < fl.size(); ++i) {
		String l = fl[i];

		if (in_comment) {
			if (l[l.length() - 1] != '\\') {
				//if escaped newline in // style comment, then this will be skipped
				in_comment = false;
				continue;
			}
		}

		String final_line;
		CharType last_char = '\0';
		int comment_start_index = 0;
		bool had_comment = false;

		for (int j = 0; j < l.length(); ++j) {
			CharType current_char = l[j];

			if (!in_multiline_comment) {
				if (last_char == '/' && current_char == '*') {
					in_multiline_comment = true;
					had_comment = true;

					final_line += l.substr_index(comment_start_index, j - 1);

					comment_start_index = j - 1;
				} else if (last_char == '/' && current_char == '/') {
					had_comment = true;
					final_line += l.substr_index(comment_start_index, j - 1);

					in_comment = true;
					break;
				}
			} else {
				if (last_char == '*' && current_char == '/') {
					comment_start_index = j + 1;

					had_comment = true;

					in_multiline_comment = false;

					//to make sure */* wont be read as both the end and beginning of a comment block on the next iteration
					++j;
					current_char = '\0';
				}
			}

			last_char = current_char;
		}

		if (in_comment) {
			if (l[l.length() - 1] != '\\') {
				//if escaped newline in // style comment, then this will be skipped
				in_comment = false;
			}
		}

		if (!had_comment && !in_multiline_comment) {
			file_lines_no_comments.push_back(l);
		} else {
			if (!final_line.empty()) {
				file_lines_no_comments.push_back(final_line);
			}
		}
	}

	fl.clear();

	//print_list(file_lines_no_comments);

	// Strip more than one empty lines in a row
	List<String> file_lines_no_comments_processed;

	int current_empty_line_count = 0;
	for (const List<String>::Element *E = file_lines_no_comments.front(); E; E = E->next()) {
		String l = E->get();

		if (l.strip_edges().empty()) {
			++current_empty_line_count;

			if (current_empty_line_count <= 1) {
				file_lines_no_comments_processed.push_back(l);
			}
		} else {
			current_empty_line_count = 0;
			file_lines_no_comments_processed.push_back(l);
		}
	}

	//print_list(file_lines_no_comments_processed);

	file_lines_no_comments.clear();

	// in global scope
	List<String> enums;
	List<String> structs;
	List<String> classes;

	enum Types {
		TYPE_NONE = 0,
		TYPE_ENUM,
		TYPE_STRUCT,
		TYPE_CLASS,
	};

	Types current_type = TYPE_NONE;
	int current_scope_level = 0;
	String current_str;
	for (const List<String>::Element *E = file_lines_no_comments_processed.front(); E; E = E->next()) {
		String l = E->get();

		if (current_type == TYPE_NONE) {
			if (l.contains("template")) {
				current_str = l + "\n";
				continue;
			}

			//Not we should be able to do this, because of how the code style is
			if (l.contains("enum ") && l.contains("{")) {
				if (l.contains("}")) {
					enums.push_back(current_str.strip_edges());
					//ERR_PRINT("TYPE_ENUM");
					//ERR_PRINT(current_str);
					current_str.clear();
					continue;
				}

				// We only care about global scope stuff, so this should always work
				current_scope_level = 1;
				current_type = TYPE_ENUM;
				current_str += l + "\n";
				continue;
			} else if (l.contains("struct ") && l.contains("{")) {
				if (l.contains("}")) {
					structs.push_back(current_str);
					//ERR_PRINT("TYPE_STRUCT");
					//ERR_PRINT(current_str);
					current_str.clear();
					continue;
				}

				current_scope_level = 1;
				current_type = TYPE_STRUCT;
				current_str += l + "\n";
				continue;
			} else if (l.contains("class ") && l.contains("{")) {
				if (l.contains("}")) {
					classes.push_back(current_str);
					//ERR_PRINT("TYPE_CLASS");
					//ERR_PRINT(current_str);
					current_str.clear();
					continue;
				}

				current_scope_level = 1;
				current_type = TYPE_CLASS;
				current_str += l + "\n";
				continue;
			}

			if (!current_str.empty()) {
				current_str.clear();
			}
		} else {
			for (int j = 0; j < l.length(); ++j) {
				CharType current_char = l[j];

				if (current_char == '}') {
					--current_scope_level;

					if (current_scope_level == 0) {
						current_str += l + "\n";

						switch (current_type) {
							case TYPE_NONE:
								//cant happen
								break;
							case TYPE_ENUM:
								enums.push_back(current_str.strip_edges());
								//ERR_PRINT("TYPE_ENUM");
								break;
							case TYPE_STRUCT:
								structs.push_back(current_str);
								//ERR_PRINT("TYPE_STRUCT");
								break;
							case TYPE_CLASS:
								classes.push_back(current_str);
								//ERR_PRINT("TYPE_CLASS");
								break;
						}

						//ERR_PRINT(current_str);

						current_type = TYPE_NONE;
						current_str.clear();
						continue;
					}
				} else if (current_char == '{') {
					++current_scope_level;
				}
			}

			current_str += l + "\n";
		}
	}

	file_lines_no_comments_processed.clear();

	structs = process_classes_and_structs(structs);
	classes = process_classes_and_structs(classes);

	//ERR_PRINT("ENUMS");
	//print_list(enums);
	//ERR_PRINT("STRUCTS");
	//print_list(structs);
	//ERR_PRINT("CLASSES");
	//print_list(classes);

	/*
	ERR_PRINT("ENUMS");

	for (const List<String>::Element *E = enums.front(); E; E = E->next()) {
		ERR_PRINT(get_structure_name(E->get()));
	}

	ERR_PRINT("STRUCTS");

	for (const List<String>::Element *E = structs.front(); E; E = E->next()) {
		ERR_PRINT(get_structure_name(E->get()));
		ERR_PRINT(get_structure_parents(E->get()));
		ERR_PRINT("=====");
		if (is_structure_template_specialization_or_parent_is_template(E->get())) {
			ERR_PRINT("!!!!!!");
		}
	}
	ERR_PRINT("CLASSES");

	for (const List<String>::Element *E = classes.front(); E; E = E->next()) {
		ERR_PRINT(get_structure_name(E->get()));
		ERR_PRINT(get_structure_parents(E->get()));
		ERR_PRINT("=====");
		if (is_structure_template_specialization_or_parent_is_template(E->get())) {
			ERR_PRINT("!!!!!!");
		}
	}*/

	//ERR_PRINT("COUNT");
	//ERR_PRINT(itos(enums.size()));
	//ERR_PRINT(itos(structs.size()));
	//ERR_PRINT(itos(classes.size()));

	HashMap<String, String> class_index;

	generate_class_index(enums, "ENUM_", &class_index);
	generate_class_index(structs, "STRUCT_", &class_index);
	generate_class_index(classes, "CLASS_", &class_index);

	//print_class_index_keys(class_index);

	String index_template = f.read_file("index_template.md.html");
	String code_template = f.read_file("code_template.md.html");
	List<String> index_template_keywords = get_template_keywords(index_template);
	HashSet<String> used_keywords;

	//print_list(index_template_keywords);

	String index_str = index_template;

	for (const List<String>::Element *E = index_template_keywords.front(); E; E = E->next()) {
		String c = E->get();

		ERR_CONTINUE_MSG(!class_index.has(c), "!class_index.has(): " + c);

		String keyword = "|||" + E->get() + "|||";

		String class_str = class_index[c];
		//String class_name = get_structure_name(class_str);

		index_str = index_str.replace(keyword, code_template.replace("$CODE$", class_str));
		used_keywords.insert(c);
	}

	f.write_file("out/index.md.html", index_str);

	//Generate a list from the unused classes.
	String index_remaining_template = f.read_file("index_remaining_template.md.html");
	String d = index_remaining_template;

	d = d.replace("$ENUMS$", generate_section_class_list(enums, "ENUM_", used_keywords));
	d = d.replace("$STRUCTS$", generate_section_class_list(structs, "STRUCT_", used_keywords));
	d = d.replace("$CLASSES$", generate_section_class_list(classes, "CLASS_", used_keywords));

	f.write_file("out/index_remaining.gen.md.html", d);
}

int main(int argc, char **argv) {
	SFWCore::setup();

	//todo create folder

	List<String> args;

	for (int i = 1; i < argc; ++i) {
		args.push_back(String::utf8(argv[i]));
	}

	for (List<String>::Element *E = args.front(); E; E = E->next()) {
		process_file(E->get());
	}

	SFWCore::cleanup();

	return 0;
}
