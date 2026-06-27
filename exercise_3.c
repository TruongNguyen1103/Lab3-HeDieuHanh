#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_func(void *arg) {
    printf("Thread dang chay, ID: %lu\n", pthread_self());
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    pthread_attr_t attr;
    size_t stacksize;
    int policy;

    /* 1. Khoi tao attr */
    pthread_attr_init(&attr);

    /* 2. Dat trang thai: JOINABLE hoac DETACHED */
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    /* 3. Dat kich thuoc stack (1MB) */
    pthread_attr_setstacksize(&attr, 1024 * 1024);

    /* 4. Dat chinh sach lap lich */
    pthread_attr_setschedpolicy(&attr, SCHED_OTHER);

    /* Kiem tra lai cac gia tri da dat */
    pthread_attr_getstacksize(&attr, &stacksize);
    pthread_attr_getschedpolicy(&attr, &policy);
    printf("Stack size: %zu bytes\n", stacksize);
    printf("Scheduling policy: %d (0=SCHED_OTHER)\n", policy);

    /* Tao thread */
    pthread_create(&tid, &attr, thread_func, NULL);

    /* Giai phong attr */
    pthread_attr_destroy(&attr);

    pthread_join(tid, NULL);
    printf("Main thread xong\n");
    return 0;
}
