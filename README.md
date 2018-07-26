hashtable
---------

[![Say Thanks!](https://img.shields.io/badge/Say%20Thanks-!-1EAEDB.svg)](https://saythanks.io/to/dizballanze)

Simple async hash table server with text protocol. The project was built for learning purpose only.

Features:

- asynchronous TCP server with epoll
- simple text protocol
- hash table with opened addressing (double hashing)
- universal hashing algorithm based on random prime numbers generation
- string hashing with Horner's rule
- auto extend table size when fill ratio >= 0.5

![usage example](usage.gif)

## Build

with Vagrant:

```
git clone git@github.com:dizballanze/hashtable.git
cd hashtable
vagrant up
vagrant ssh
cd proj
make
```

## Protocol

Protocol supports four operations:

- `SET <key> <value>\n` - sets `<key>` with `<value>`
- `GET <key>\n` - gets `<key>` from hash table if exists
- `DELETE <key>\n` - remove `<key>` from hash table if exists
- `COUNT\n` - count of items in hash table

## Usage

Start server:

```
$ ./hashtable 0.0.0.0 31337
Ready to accept connection on 0.0.0.0:31337...
```

Connect to server (by telnet for example):

```
$ telnet 127.0.0.1 31337
Connected to 127.0.0.1.

SET mykey Hello World!
DONE

GET mykey
DONE
Hello World!

SET foo bar
DONE

COUNT
DONE
2

DELETE foo
DONE

COUNT
DONE
1
```

## LICENSE

The MIT License (MIT)

Copyright Yuri Shikanov (c) 2016 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
