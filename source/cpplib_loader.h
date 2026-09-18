/* cpplib_loader.h -- load libc++_shared.so for __ndk1 symbol resolution
 *
 * Copyright (C) 2026 givethesourceplox
 *
 * This is a minimal ELF loader specifically designed to load
 * libc++_shared.so from the Bully APK. It maps the library into
 * heap memory, resolves its imports against our existing libc/libm,
 * applies relocations, and exports a symbol lookup function.
 */

#ifndef __CPPLIB_LOADER_H__
#define __CPPLIB_LOADER_H__

#include <stdint.h>
#include <elf.h>

#ifdef __cplusplus
extern "C" {
#endif

int cpplib_load(const char *filename);
uintptr_t cpplib_find_symbol(const char *name);
int cpplib_resolve_symbol(const char *name, uintptr_t *out_addr);

// exposes the loaded libc++_shared.so's runtime base + (unmodified, link-time)
// program headers so so_dl_iterate_phdr() can report this module too. Returns
// 0 if the library hasn't been loaded yet. out_phdr/out_phnum may be set even
// if the module has no phdrs to report (out_phnum == 0).
int cpplib_get_phdr_info(uintptr_t *out_virtbase, const char **out_name,
                          const Elf64_Phdr **out_phdr, int *out_phnum);

#ifdef __cplusplus
}
#endif

#endif
