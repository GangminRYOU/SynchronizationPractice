#include <Windows.h>
#include <stdio.h>
#include <process.h>
#define THREAD_COUNT 100

volatile LONG lock = 0;
volatile int num = 0;

void acquire_lock(void) {
	while (_InterlockedExchange(&lock, 1) == 1) {
		Sleep(0);
	}
}

void release_lock(void) {
	_InterlockedExchange(&lock, 0);
}


DWORD WINAPI thread_func(LPVOID lpParam) {

	acquire_lock();
	num += 1;
	release_lock();
}


int main(void) {
	HANDLE Thread[THREAD_COUNT];
	for (int i = 0; i < THREAD_COUNT; i++) {
		Thread[i] = CreateThread(NULL, 0, thread_func, NULL, 0, NULL);
	}

	WaitForMultipleObjects(100, Thread, TRUE, INFINITE);
	printf("%d\n", num);
	return (0);
}
