# `OB_table`

`OB_table` is an open bucket hash table, implementing a set (which can be used
to implement a map / dictionary etc.).

This is a very simple and small implementation I provide under CC0 (I won't sue
you for copying the code, yes even if you don't attribute me).

I have profiled this running significantly faster than e.g. libstdc++
`std::unordered_map` (using good hashes, allocaters, etc. in both).

## Example

See `tests/OB_table_test.c` for a simple example.

## Open buckets

Open bucket hash tables use just one big array and will walk through the array
itself, rather than a linked list or something else if a collision occurs.

Open buckets improve:

* Caching, since memory is trivially just allocated in one place for the table.
  Of course, this is not the whole fight.
* Simplicity, it turns out using a big array for everything is simpler.
* Memory usage, even with very large capacity:storage ratios the `OB_table` will
  use a lot less memory than a linked list closed bucket implementation...
  because there are no allocations for the list nodes. This was the most
  surprising part to me because I'm used to trading space for performance. This
  memory efficiency also implicitly improves caching.

Open buckets are 'worse' when you have many random insertions and deletions from
the table. This can be approached in a number of ways, but the best general
approach is to say this up-front and then let the implementor choose when to
reshuffle the table (which is done by init'ing a new `OB_table`, inserting
all old table contents, and clearing the old table).

Open buckets with linear probing like mine (look at the nearby indexes for the
entry on collision) *must* use good hashes, like pseudo-random hashes, which are
luckily plentiful and fast now. Otherwise the linear probing is making a bad
assumption, that it doesn't need to further 'shuffle' the table. A good hash
function is better than using another probing method which will kill your
throughput (linear probing obviously has better locality).

The important thing to realise about the 'downsides' of open buckets is that
they were probably exagerrated to you, the same way that 'linked lists' were
probably overrepresented. But as slow as a linked list is, an open bucket hash
table is fast. And even in the cases where you would expect it to perform worse
it will still perform admirably, as well as alternatives. So not quite as
drastic as arrays vs linked lists but it is a similar matter.

## Linear probing 'pitfalls'

If you see a critique or study of open addressing or open hashing that implies
it's not up to scratch, have a look and make sure they are using a good, random
hashing function (at least as 'good' as md5, it needs to look like noise on
their input), and uses *linear probing*. I think I have seen multiple studies
using complicated probing schemes and bad hashes as evidence open buckets
don't work or aren't as good as closed buckets. But really they are just using
a bad case to prove a bad rule: why would you make decisions based on bad hashes
or bad probing?

Why do other probing methods exist? Because of bad hashes. Performance in open
buckets gets *horrific* with mediocre hashes and linear probing. So other
probing techniques are there to prevent it getting quite as bad.

But using anything other than linear probing will cap your throughput in a nasty
way because you trash the locality of the array. In fact, ask yourself *why* you
would read from an array in any order other than linearly? Why even use an array
at that point? It makes an array behave like a linked list: bad.

The mentioning of probing schemes is a big distraction, in my opinion. Don't
make decisions based on hypotheticals like "what if my hash function is bad".
Do you want the best performance? Then use open addressing with linear probing
and the best hash functions: you get best caching performance from a hash table
possible, and it's capable of spread (by placing more requirements on the hash
function, but we can handle that because we want the *best* and it goes without
saying the best hash table would be used with the best hashes).
