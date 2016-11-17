#include <stdio.h>
#include <iostream>
#include <assert.h>
// this header for SSE compiler
#include <immintrin.h>

int main() {

	int *buffer;
	int *buffer_maloc;
	buffer_maloc = (int*)_aligned_malloc(sizeof(int) * 1000, 16);
	// first buufer
	buffer = new  int[1000];
	memset(buffer, 100, 1000);
	__m128i zero = _mm_setzero_si128();
	for (__m128i *i = reinterpret_cast<__m128i*>(buffer), *end = reinterpret_cast<__m128i*>(&buffer[1000]);i < end;i++) {
		_mm_store_si128(i, zero);
	}
	// second buffer
	const __m128i value_maloc = _mm_set1_epi32(10);
	for (__m128i *i = reinterpret_cast<__m128i*>(buffer_maloc), *end = reinterpret_cast<__m128i*>(&buffer_maloc[1000]);i < end;i++) {
		_mm_store_si128(i, value_maloc);
	}

	for (unsigned int id = 0;id != 1000;id++) {
		std::cout << " " << buffer_maloc[id] << std::endl;
	}

	delete[] buffer;
	/*delete buffer_maloc;*/

	while (1){

		std::cout << "Hello world" << std::endl;
		std::cout << "My name's Tho Cao " << std::endl;
		break;
	}
	while (true)
	{
		//std::cout << "Now I want to see the different things when i use Github.com" << std::endl;
	}


	return 0;
}