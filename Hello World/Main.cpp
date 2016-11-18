#include <stdio.h>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <fstream>
// this header for SSE compiler
#include <immintrin.h>
// check thi apability of CPU
#include "Cpuid.h"
// SSE3 for Shuffle
#include <tmmintrin.h>
#include "Timer.h"
#include "FrameTimer.h"

extern "C" bool GetAVXSupportFlag();

// loop for calculate vector
void SumVectorSSE(int n, float alpha, float *X, float *Y) {
	__m128 x_vec, y_vec,res_vec; /*Pointers to vector*/
	int i;
	const __m128 a_vec = _mm_set1_ps(alpha);
	for (i = 0; i < n ; i+=4) {
		x_vec = _mm_load_ps(&X[i]);
		y_vec = _mm_load_ps(&Y[i]);
		res_vec = _mm_add_ps(_mm_mul_ps(a_vec, x_vec), y_vec);
		_mm_store_ps(&Y[i], res_vec);
	}
}

void SumVector(int n, float alpha, float *X, float *Y) {
	for (int i = 0; i != n; i++) {
		Y[i] = alpha*X[i] + Y[i];
	}
}

void SumVectorAVX(int n, float alpha, float *X, float *Y) {
	__m256 x_vec, y_vec, res_vec;
	const __m256 a_vec = _mm256_set1_ps(alpha);
	for (int i = 0; i < n; i += 8) {
		x_vec = _mm256_load_ps(&X[i]);
		y_vec = _mm256_load_ps(&Y[i]);
		res_vec = _mm256_add_ps(_mm256_mul_ps(a_vec, x_vec), y_vec);
		_mm256_store_ps(&Y[i], res_vec);
	}
}
int main() {

	float alpha = 3;
	const int n = 10000000;
	float *a;
	float *b;
	a = (float*)_mm_malloc (sizeof(float) * n, 16);
	// first buufer
	b = (float*) _mm_malloc(sizeof(float) * n, 16);

	//memset(buffer, 100, 1000);
	//__m128i zero = _mm_setzero_si128();
	//for (__m128i *i = reinterpret_cast<__m128i*>(buffer), *end = reinterpret_cast<__m128i*>(&buffer[1000]);i < end;i++) {
	//	_mm_store_si128(i, zero);
	//}
	//// second buffer
	//const __m128i value_maloc = _mm_set1_epi32(10);
	//for (__m128i *i = reinterpret_cast<__m128i*>(buffer_maloc), *end = reinterpret_cast<__m128i*>(&buffer_maloc[1000]);i < end;i++) {
	//	_mm_store_si128(i, value_maloc);
	//}
	//for (unsigned int id = 0;id != 1000;id++) {
	//	std::cout << " " << buffer_maloc[id] << std::endl;
	//}

	std::wofstream logFile(L"logfile.txt");
	FrameTimer ft;
	while (1){

		std::cout << "Hello world" << std::endl;
		std::cout << "My name's Tho Cao " << std::endl;
		if (InstructionSet::AVX512F()) {
			std::cout << "AVX512" << std::endl;
		}
		if (InstructionSet::AVX()) {
			std::cout << "AVX" << std::endl;
		}
		if (InstructionSet::AVX512CD()) {
			std::cout << "AVX512CD" << std::endl;
		}

		if (GetAVXSupportFlag()) {
			std::cout << "You have AVX" << std::endl;
		}
		else {
			std::cout << "You have no AVX" << std::endl;
		}
		break;
	}
	int k = 0;
	while (k!=100)
	{

		ft.StartFrame();
		SumVectorAVX(n, alpha, a, b);
		ft.StopFrame(logFile);
		k++;
		//std::cout << "Now I want to see the different things when i use Github.com" << std::endl;
	}

	/*delete buffer_maloc;*/
	_mm_free(a);
	_mm_free(b);
	return 0;
}