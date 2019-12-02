# cpp-lazy-split
c++ lazy string split

this is a lazy splitter for strings that avoids allocations and fetches the results as needed , this allows to parse the string while splitting

also the delim string may be a one char or a string

currently requires a c++ 17 compiler for the iterators splitter and a c++ 20 compiler for the coroutines splitter

this can be ported to pre c++ 17 by implementing a string view but this is out the scope of this project

Don't copy without contacting me !
