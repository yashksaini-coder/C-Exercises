# Authoring conventions

Every exercise N (three-digit id `NNN`) consists of four files. Follow these
conventions exactly; the Makefile and tests depend on them.

## 1. `exercises/NNN.md` — the instructions

Model: `exercises/001.md`. Structure:

```
# NNN — Title

Implement `<exact prototype from include/exercises.h>` in `NNN.c`.

<2–6 short paragraphs: the contract (inputs, outputs, edge cases, ownership,
what to return on failure), what the exercise teaches, and anything the
learner must NOT do (e.g. "do not call strlen", "no global state").>

Examples: <2–4 concrete input → output pairs, mirroring the tests>.

> [!TIP]
> Read: <guide name>, §x.y Title — <URL of the split chapter page>
> (optional second line: why it is asked in interviews)

Run `make run N=<n>`; check with `make test N=<n>`.
```

- Plain, direct English. No filler. The learner is self-paced, so the `.md`
  must be enough on its own.
- Link the Beej chapter page from the split HTML guides. Exact page slugs:
  - BGC base `https://beej.us/guide/bgc/html/split/` + one of:
    `variables-and-statements.html`, `functions.html`, `pointers.html`,
    `arrays.html`, `strings.html`, `structs.html`, `file-inputoutput.html`,
    `typedef-making-new-types.html`, `pointers2.html`,
    `manual-memory-allocation.html`, `scope.html`, `types-ii-way-more-types.html`,
    `types-iii-conversions.html`, `types-iv-qualifiers-and-specifiers.html`,
    `multifile-projects.html`, `the-outside-environment.html`,
    `the-c-preprocessor.html`, `structs-ii-more-fun-with-structs.html`,
    `characters-and-strings-ii.html`, `enumerated-types-enum.html`,
    `pointers-iii-pointers-to-pointers-and-more.html`, `bitwise-operations.html`,
    `variadic-functions.html`, `exiting-a-program.html`, `goto.html`,
    `types-part-v-compound-literals-and-generic-selections.html`,
    `incomplete-types.html`, `fixed-width-integer-types.html`,
    `multithreading.html`, `chapter-atomics.html`.
  - BGNET base `https://beej.us/guide/bgnet/html/split-wide/` + one of:
    `what-is-a-socket.html`, `ip-addresses-structs-and-data-munging.html`,
    `jumping-from-ipv4-to-ipv6.html`, `system-calls-or-bust.html`,
    `client-server-background.html`, `slightly-advanced-techniques.html`,
    `common-questions.html`, `man-pages.html`.
    If unsure of a page slug, link the guide index instead.
- Mention which standard functions are allowed. The default rule: the exercise
  must not call the library function it reimplements (`my_strlen` may not call
  `strlen`), but any _earlier_ exercise's function may be reused.

## 2. `exercises/NNN.c` — the stub the learner edits

Model: `exercises/001.c`.

```c
#include "exercises.h"
#include "lib.h"
/* extra standard headers the solution will need, already included */

/* One-line doc comment. */
<prototype> {
    (void)each_parameter;
    /* TODO: implement. */
    return <neutral value: 0, false, NULL, -1>;
}

#ifndef EXERCISE_TEST
int main(void) {
    /* a tiny playground call that prints something, or `return 0;` */
    return 0;
}
#endif
```

- Every function declared for the exercise in `exercises.h` must have a stub.
- Opaque types (e.g. `struct Counter`) are **defined in the exercise `.c`**;
  the stub must contain the struct definition with a `/* TODO */` body hint
  so the stub compiles and tests link.
- Stubs must compile cleanly with `-std=c11 -Wall -Wextra -Wpedantic`.

## 3. `solutions/NNN.c` — the reference solution

Same shape as the stub, fully implemented, idiomatic, commented where a
decision is non-obvious. Must pass `make test N=<n> SOLUTION=1` **and**
`make test N=<n> SOLUTION=1 SANITIZE=1` (no leaks, no UB).

## 4. `tests/stageK.c` — the tests for a whole stage

One file per stage, K = stage number. Model: `tests/stage1.c`. Shape:

```c
#include "support.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef int stage_K_keep_translation_unit_nonempty;

#if EXERCISE == 11
void run_tests(void) { ... }
#elif EXERCISE == 12
void run_tests(void) { ... }
...
#endif
```

- Exactly one `run_tests` per exercise number; the chain covers only the
  stage's range so other stage files compile to nothing for that number.
- Open each scenario with `CASE("short description of input")` then checks:
  `INT`, `UINT`, `BOOL`/`TRUE`/`FALSE`, `DOUBLE`/`DOUBLE_NEAR`, `STRING`,
  `BYTES`, `ARRAY`, `POINTER`, `NOT_NULL`, `IS_NULL` (see `tests/support.h`).
- 3–6 cases per exercise: a normal case, boundaries (empty, size 0, NULL
  where the contract allows it, INT_MIN/INT_MAX), and the one subtle bug a
  typical first attempt has.
- Tests must free everything they allocate and everything the exercise hands
  back, so `SANITIZE=1` passes against the reference solution.
- Tests must be deterministic and finish well under 10 seconds. Networking
  tests use `socketpair()` or the loopback address and port `"0"`/an ephemeral
  port obtained via `getsockname`; threading tests use small counts.
- Never call the function under test from _another_ exercise's test unless the
  `.md` says it is a dependency.

## Verification commands (run per exercise)

```bash
make test N=<n> SOLUTION=1
make test N=<n> SOLUTION=1 SANITIZE=1
make test N=<n>                       # the stub must compile and FAIL cleanly
cc -std=c11 -Wall -Wextra -Wpedantic -Iinclude -I. -Itests -fsyntax-only exercises/NNN.c
```

## Images (`docs/assets/`)

| File                   | Size     | Used in                                              |
| ---------------------- | -------- | ---------------------------------------------------- |
| `banner.png`           | 1408×416 | top of `README.md`                                   |
| `roadmap.png`          | 1608×536 | `README.md` index, `exercises/README.md`, `docs/roadmap.md` |
| `stage-NN.png`         | 160×160  | stage table in `README.md`, stage headings in both indexes (shown at 32–40px) |
| `social-preview.png`   | 1280×640 | GitHub → Settings → Social preview (not linked from Markdown) |

A new stage needs a `stage-NN.png` in the same 160×160 pixel style, referenced
in all three places above.
