import os
from glob import glob


def find_all_sources(path_to_dir):
	return glob(path_to_dir + "*.c")


def get_source_content(source_path):
	with open(source_path, 'r') as source:
		return source.read()


def apply_modif(content, source_path):
	with open(source_path, 'w') as source:
		source.write(content)


def change_content(content):
	content = content.replace("    ", "\t")
	content = content.replace("\t ", "\t")
	content = content.replace(" \n", "\n")
	content = content.replace("  ", " ")
	return content


def norme_libft():
	lib_path = os.path.split(os.path.dirname(__file__))[0] + "/libft/srcs/"
	srcs = list()
	for src in find_all_sources(lib_path) + find_all_sources(lib_path + "Linux/") + find_all_sources(
					lib_path + "Darwin/"):
		srcs.append(src)
		content = get_source_content(src)
		new = change_content(content)
		if content != new:
			print src
			apply_modif(new, src)


def norme_gnl():
	gnl_path = os.path.split(os.path.dirname(__file__))[0] + "/get_next_line/get_next_line.c"
	content = get_source_content(gnl_path)
	new = change_content(content)
	if content != new:
		print "norme !"
		apply_modif(new, gnl_path)


def norme_ls():
	ls_path = os.path.split(os.path.dirname(__file__))[0] + "/ls/srcs/"
	srcs = []
	for src in find_all_sources(ls_path):
		srcs.append(src)
		content = get_source_content(src)
		new = change_content(content)
		if content != new:
			print "norme !"
			apply_modif(new, src)


if __name__ == "__main__":
	norme_ls()