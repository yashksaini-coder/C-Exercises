# Exercise index

Work in order within a stage; stages can be taken in any order once you are
past Stage 3. Read the `.md`, experiment in the matching `.c` file, then run
`make test N=<number>`. Each stage points at the chapter of Beej's guides it
draws from.

- **BGC** = [Beej's Guide to C Programming](https://beej.us/guide/bgc/html/split/)
- **BGNET** = [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/split-wide/index.html)

## Stage 1 — Foundations (BGC ch. 2–4, 14)

| #   | Function        | Instructions                            |
| --- | --------------- | --------------------------------------- |
| 1   | `sign`          | [Sign of an integer](001.md)            |
| 2   | `max_of_three`  | [Largest of three](002.md)              |
| 3   | `is_leap_year`  | [Leap years](003.md)                    |
| 4   | `gcd`           | [Greatest common divisor](004.md)       |
| 5   | `is_prime`      | [Primality](005.md)                     |
| 6   | `digit_sum`     | [Sum of digits](006.md)                 |
| 7   | `fibonacci`     | [Fibonacci without recursion](007.md)   |
| 8   | `add_overflows` | [Detect signed overflow safely](008.md) |
| 9   | `average`       | [Integer to floating point](009.md)     |
| 10  | `collatz_steps` | [Loops with unsigned 64-bit](010.md)    |

## Stage 2 — Pointers and arrays (BGC ch. 5, 6, 11, 23)

| #   | Function                   | Instructions                             |
| --- | -------------------------- | ---------------------------------------- |
| 11  | `swap_int`                 | [Swap through pointers](011.md)          |
| 12  | `array_max_index`          | [Index of the maximum](012.md)           |
| 13  | `array_reverse`            | [Reverse in place](013.md)               |
| 14  | `array_rotate_left`        | [Rotate by k](014.md)                    |
| 15  | `find_index`               | [Linear search with ptrdiff_t](015.md)   |
| 16  | `pointer_distance`         | [Pointer subtraction](016.md)            |
| 17  | `matrix_transpose`         | [Two-dimensional arrays](017.md)         |
| 18  | `apply_each`               | [Function pointers](018.md)              |
| 19  | `count_matching`           | [Predicates as callbacks](019.md)        |
| 20  | `remove_duplicates_sorted` | [Two-pointer compaction](020.md)         |

## Stage 3 — Strings (BGC ch. 7, 15, 21)

| #   | Function         | Instructions                         |
| --- | ---------------- | ------------------------------------ |
| 21  | `my_strlen`      | [String length](021.md)              |
| 22  | `my_strcpy`      | [Copy a string](022.md)              |
| 23  | `my_strcmp`      | [Compare strings](023.md)            |
| 24  | `my_strchr`      | [Find a character](024.md)           |
| 25  | `my_strstr`      | [Find a substring](025.md)           |
| 26  | `reverse_string` | [Reverse in place](026.md)           |
| 27  | `is_palindrome`  | [Palindromes, ignoring noise](027.md)|
| 28  | `trim`           | [Trim whitespace in place](028.md)   |
| 29  | `count_words`    | [Count words](029.md)                |
| 30  | `my_atoi`        | [String to int with clamping](030.md)|
| 31  | `int_to_string`  | [Int to decimal string](031.md)      |
| 32  | `compress_runs`  | [Run-length encoding](032.md)        |

## Stage 4 — Structs, enums, unions, bit-fields (BGC ch. 8, 10, 20, 22)

| #   | Function                                     | Instructions                                  |
| --- | -------------------------------------------- | --------------------------------------------- |
| 33  | `point_distance`                             | [Structs by value](033.md)                    |
| 34  | `rect_area`, `rect_contains`                 | [Nested structs](034.md)                      |
| 35  | `compare_students`                           | [qsort comparator on structs](035.md)         |
| 36  | `day_name`, `next_day`                       | [Enums as types](036.md)                      |
| 37  | `record_from_weight`                         | [offsetof and container_of](037.md)           |
| 38  | `float_bits`, `bits_to_float`                | [Unions and type punning](038.md)             |
| 39  | `encode_permissions`, `decode_permissions`   | [Bit-fields](039.md)                          |
| 40  | `owned_string_new`                           | [Flexible array members](040.md)              |

## Stage 5 — Memory (BGC ch. 12, 16, 35)

| #   | Function                                | Instructions                                  |
| --- | --------------------------------------- | --------------------------------------------- |
| 41  | `my_strdup`                             | [Duplicate a string](041.md)                  |
| 42  | `array_clone`                           | [Clone an array](042.md)                      |
| 43  | `vector_push`, `vector_free`            | [Growable vector with realloc](043.md)        |
| 44  | `string_join`                           | [Join strings into owned memory](044.md)      |
| 45  | `read_line`                             | [Read a line of any length](045.md)           |
| 46  | `arena_init`, `arena_alloc`, `arena_free` | [Arena allocator with alignment](046.md)    |
| 47  | `matrix_alloc`, `matrix_free`           | [2D allocation in one block](047.md)          |
| 48  | `my_calloc`                             | [Overflow-checked allocation](048.md)         |
| 49  | `sb_append`, `sb_finish`                | [String builder with ownership](049.md)       |
| 50  | `pool_init`, `pool_get`, `pool_put`, `pool_free` | [Fixed-size block pool](050.md)      |

## Stage 6 — Bits and bytes (BGC ch. 24, 37; BGNET §3.2, §7.5)

| #   | Function            | Instructions                             |
| --- | ------------------- | ---------------------------------------- |
| 51  | `bit_count`         | [Popcount](051.md)                       |
| 52  | `is_power_of_two`   | [Powers of two](052.md)                  |
| 53  | `reverse_bits`      | [Reverse 32 bits](053.md)                |
| 54  | `bit_set`           | [Set and clear a bit](054.md)            |
| 55  | `read_u32_be`       | [Decode big-endian bytes](055.md)        |
| 56  | `write_u32_be`      | [Encode big-endian bytes](056.md)        |
| 57  | `my_htons`, `my_htonl` | [Host and network byte order](057.md) |
| 58  | `pack`              | [Variadic packer (BGNET pack)](058.md)   |
| 59  | `unpack`            | [Variadic unpacker](059.md)              |
| 60  | `internet_checksum` | [RFC 1071 checksum](060.md)              |

## Stage 7 — Object-oriented C (BGC §20.7, §23.7, ch. 35, §32.2)

| #   | Function                                        | Instructions                              |
| --- | ----------------------------------------------- | ----------------------------------------- |
| 61  | `counter_new`, `counter_increment`, `counter_get`, `counter_free` | [Opaque types](061.md)  |
| 62  | `shape_new_circle`, `shape_new_rectangle`, `shape_area`, `shape_perimeter`, `shape_name`, `shape_free` | [Virtual tables](062.md) |
| 63  | `generic_max`                                   | [Generic code with void *](063.md)        |
| 64  | `my_qsort`                                      | [Generic sort](064.md)                    |
| 65  | `my_bsearch`                                    | [Generic binary search](065.md)           |
| 66  | `emitter_connect`, `emitter_emit`               | [Callbacks with context](066.md)          |
| 67  | `animal_new_dog`, `animal_new_cat`, `animal_speak`, `animal_free` | [Inheritance by embedding](067.md) |
| 68  | `describe_int`, `describe_double`, `describe_string` | [_Generic selections](068.md)        |

## Stage 8 — Data structures (interview core)

| #   | Function                                        | Instructions                              |
| --- | ----------------------------------------------- | ----------------------------------------- |
| 69  | `stack_push`, `stack_pop`                       | [Array-backed stack](069.md)              |
| 70  | `queue_enqueue`, `queue_dequeue`                | [Ring-buffer queue](070.md)               |
| 71  | `list_push_back`, `list_length`, `list_free`    | [Singly linked list](071.md)              |
| 72  | `list_reverse`                                  | [Reverse a linked list](072.md)           |
| 73  | `list_has_cycle`                                | [Floyd's cycle detection](073.md)         |
| 74  | `list_merge_sorted`                             | [Merge two sorted lists](074.md)          |
| 75  | `hash_djb2`, `hashmap_put`, `hashmap_get`, `hashmap_free` | [Hash map with chaining](075.md) |
| 76  | `bst_insert`, `bst_contains`, `bst_free`        | [Binary search tree](076.md)              |
| 77  | `bst_height`, `bst_to_sorted_array`             | [Tree recursion](077.md)                  |
| 78  | `heap_push`, `heap_pop`                         | [Binary min-heap](078.md)                 |
| 79  | `lru_init`, `lru_get`, `lru_put`, `lru_free`    | [LRU cache](079.md)                       |

## Stage 9 — Environment and toolchain (BGC ch. 9, 17–19, 25, 28, 31)

| #   | Function                        | Instructions                                   |
| --- | ------------------------------- | ---------------------------------------------- |
| 80  | `parse_args`                    | [Command-line arguments](080.md)               |
| 81  | `copy_file`                     | [File I/O](081.md)                             |
| 82  | `count_lines`                   | [Reading until EOF](082.md)                    |
| 83  | `write_records`, `read_records` | [Binary file I/O](083.md)                      |
| 84  | `sum_ints`                      | [Variadic functions](084.md)                   |
| 85  | `log_message`                   | [va_list and vsnprintf](085.md)                |
| 86  | `safe_min_calls`                | [Macro pitfalls](086.md)                       |
| 87  | `safe_divide`, `error_string`   | [Error codes and errno style](087.md)          |
| 88  | `load_config`, `config_free`    | [goto cleanup and ownership](088.md)           |

## Stage 10 — Networking (BGNET ch. 3, 5, 6, 7)

| #   | Function                   | Instructions                                     |
| --- | -------------------------- | ------------------------------------------------ |
| 89  | `parse_ipv4`               | [Parse dotted-quad](089.md)                      |
| 90  | `format_ipv4`              | [Format dotted-quad](090.md)                     |
| 91  | `ipv4_in_subnet`           | [CIDR masks](091.md)                             |
| 92  | `parse_host_port`          | [host:port and [v6]:port](092.md)                |
| 93  | `sockaddr_to_string`       | [struct sockaddr and inet_ntop](093.md)          |
| 94  | `send_all`                 | [Handling partial sends](094.md)                 |
| 95  | `recv_exact`               | [Reading exactly n bytes](095.md)                |
| 96  | `send_frame`, `recv_frame` | [Length-prefixed framing](096.md)                |
| 97  | `tcp_listen`               | [getaddrinfo, socket, bind, listen](097.md)      |
| 98  | `tcp_connect`              | [Client connect](098.md)                         |
| 99  | `echo_serve_one`           | [accept and echo](099.md)                        |
| 100 | `wait_readable`            | [poll()](100.md)                                 |
| 101 | `resolve_ipv4`             | [DNS via getaddrinfo](101.md)                    |
| 102 | `parse_request_line`       | [Parsing an HTTP request line](102.md)           |

## Stage 11 — Concurrency (BGC ch. 39, 40; POSIX threads)

| #   | Function                                     | Instructions                             |
| --- | -------------------------------------------- | ---------------------------------------- |
| 103 | `parallel_sum`                               | [Create and join threads](103.md)        |
| 104 | `safe_counter_*`                             | [Mutex-protected state](104.md)          |
| 105 | `bounded_queue_*`                            | [Condition variables](105.md)            |
| 106 | `atomic_hit`, `atomic_hits`, `atomic_hits_reset` | [Atomics](106.md)                    |
| 107 | `once_init_value`                            | [Run-once initialization](107.md)        |

## Stage 12 — Interview classics

| #   | Function                | Instructions                                  |
| --- | ----------------------- | --------------------------------------------- |
| 108 | `two_sum`               | [Two sum](108.md)                             |
| 109 | `balanced_brackets`     | [Balanced brackets](109.md)                   |
| 110 | `reverse_words`         | [Reverse words in place](110.md)              |
| 111 | `longest_common_prefix` | [Longest common prefix](111.md)               |
| 112 | `merge_sorted_arrays`   | [Merge sorted arrays](112.md)                 |
| 113 | `kth_largest`           | [Quickselect](113.md)                         |
| 114 | `next_token`            | [Re-entrant tokenizer (strtok_r)](114.md)     |
| 115 | `bigint_add`            | [Add big integers as strings](115.md)         |
| 116 | `evaluate_rpn`          | [Evaluate reverse Polish notation](116.md)    |
