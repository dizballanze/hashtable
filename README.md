hashtable
---------

Simple async hash table server with text protocol. Project was build for learning purpose only.

Features:

- asyncronous TCP server with epoll
- simple text protocol
- hash table with opened addressing (double hashing)
- universal hashing algorithm based on random prime numbers generation
- auto extend table size where fill ration >= 0.5


## Build

with Vagrant:

```
git clone git@github.com:dizballanze/hashtable.git
cd hashtable
vagrant up
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
