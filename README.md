Cache
============

The idea of caching items for fast retrieval goes back nearly to the beginning of the computer science. We also use that idea and use a LRU cache for storing morphological analyses of surface forms. Before analyzing a surface form, we first look up to the cache, and if there is an hit, we just take the analyses from the cache. If there is a miss, we analyze the surface form and put the morphological analyses of that surface form in the LRU cache. As can be expected, the speed of the caching mechanism surely depends on the size of the cache.

For Developers
============

You can also see [Java](https://github.com/starlangsoftware/DataStructure), 
[Python](https://github.com/starlangsoftware/DataStructure-Py), [Cython](https://github.com/starlangsoftware/DataStructure-Cy), 
[C++](https://github.com/starlangsoftware/DataStructure-CPP), [Swift](https://github.com/starlangsoftware/DataStructure-Swift), [Php](https://github.com/starlangsoftware/DataStructure-Php), 
[Js](https://github.com/starlangsoftware/DataStructure-Js), or [C#](https://github.com/starlangsoftware/DataStructure-CS) repository.

## Requirements

* [C Compiler](#cpp)
* [Git](#git)


### CPP
To check if you have compatible C Compiler installed,
* Open CLion IDE 
* Preferences >Build,Execution,Deployment > Toolchain  

### Git

Install the [latest version of Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).

## Download Code

In order to work on code, create a fork from GitHub page. 
Use Git for cloning the code to your local or below line for Ubuntu:

	git clone <your-fork-git-link>

A directory called DataStructure will be created. Or you can use below link for exploring the code:

	git clone https://github.com/starlangsoftware/DataStructure-C.git

## Open project with CLion IDE

To import projects from Git with version control:

* Open CLion IDE , select Get From Version Control.

* In the Import window, click URL tab and paste github URL.

* Click open as Project.

Result: The imported project is listed in the Project Explorer view and files are loaded.


## Compile

**From IDE**

After being done with the downloading and opening project, select **Build Project** option from **Build** menu. After compilation process, user can run DataStructure-CPP.

Detailed Description
============

+ [CounterHashMap](#counterhashmap)
+ [LRUCache](#lrucache)

## CounterHashMap

CounterHashMap bir veri tipinin kaç kere geçtiğini hafızada tutmak için kullanılmaktadır.

Bir CounterHashMap yaratmak için

	a = create_counter_hash_map(int (*hash_function)(void*, int), int (*key_compare)(void*, void*))

Hafızaya veri eklemek için

	void put_counter_hash_map(Counter_hash_map_ptr counter_hash_map, void* key)

Örneğin,

	put_counter_hash_map(a, "ali");

Bu aşamanın ardından "ali" nin sayacı 1 olur.

Hafızaya o veriyi birden fazla kez eklemek için

	void put_counter_hash_map_n_times(Counter_hash_map_ptr counter_hash_map, void* key, int N)

Örneğin,

	put_counter_hash_map_n_times(a, "veli", 5)

Bu aşamanın ardından "ali"'nin sayacı 5 olur.

Hafızada o verinin kaç kere geçtiğini bulmak için

	int count_counter_hash_map(Counter_hash_map_ptr counter_hash_map, void* key)

Örneğin, "veli" nin kaç kere geçtiğini bulmak için

	kacKere = count_counter_hash_map(a, "veli")

Bu aşamanın ardından kacKere değişkeninin değeri 5 olur.

Hafızada hangi verinin en çok geçtiğini bulmak için

	void* max_counter_hash_map(Counter_hash_map_ptr counter_hash_map)

Örneğin,

	kelime = max_counter_hash_map(a)

Bu aşamanın ardından kelime "veli" olur.

## LRUCache

LRUCache veri cachelemek için kullanılan bir veri yapısıdır. LRUCache en yakın zamanda 
kullanılan verileri öncelikli olarak hafızada tutar. Bir LRUCache yaratmak için

	Lru_cache_ptr create_lru_cache(int cache_size, int (*hash_function)(void*, int), int (*compare)(void*, void*))

kullanılır. cacheSize burada cachelenecek verinin büyüklüğünün limitini göstermektedir.

Cache'e bir veri eklemek için

	void lru_cache_add(Lru_cache_ptr lru_cache, void* key, void* data)

kullanılır. data burada eklenecek veriyi, key anahtar göstergeyi göstermektedir.

Cache'de bir veri var mı diye kontrol etmek için

	int lru_cache_contains(Lru_cache_ptr lru_cache, void* key)

kullanılır.

Cache'deki veriyi anahtarına göre getirmek için

	void* lru_cache_get(Lru_cache_ptr lru_cache, void* key)

kullanılır.
