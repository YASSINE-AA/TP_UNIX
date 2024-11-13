#include "src_cli_fifo.h"
#include "unity.h"
#include "utils.h"
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO1 "tmp/fifo1"
pthread_t writer_thread_id, reader_thread_id;

void setUp(void) {}

void tearDown(void) {}

void test_create_fifo(void) {
  create_fifo(FIFO1);
  TEST_ASSERT_EQUAL(0, access(FIFO1, F_OK));
  close_fifo(FIFO1);
}

void *reader_thread(void *arg) {
  message *received_msg = NULL;
  read_fifo(FIFO1, &received_msg);

  TEST_ASSERT_EQUAL(1234, received_msg->pid);
  TEST_ASSERT_EQUAL(5, received_msg->content_size);
  TEST_ASSERT_EQUAL_STRING("test", received_msg->content);

  free(received_msg);

  return NULL;
}

void *writer_thread(void *arg) {
  message *test_msg = malloc(sizeof(message) + 5);
  test_msg->pid = 1234;
  test_msg->content_size = 5;
  strcpy(test_msg->content, "test");

  write_fifo(FIFO1, test_msg);

  free(test_msg);

  return NULL;
}

void test_write_and_read_fifo(void) {
  create_fifo(FIFO1);

  pthread_create(&reader_thread_id, NULL, reader_thread, NULL);
  pthread_create(&writer_thread_id, NULL, writer_thread, NULL);

  pthread_join(reader_thread_id, NULL);
  pthread_join(writer_thread_id, NULL);

  close_fifo(FIFO1);
}

void test_generate_random_number(void) {
  char *random_num = generate_random_number();
  TEST_ASSERT_NOT_NULL(random_num);
  int num = atoi(random_num);
  TEST_ASSERT_TRUE(num >= 0 && num < MAX);
  free(random_num);
}

void test_generate_random_number_sequence(void) {
  char *sequence = generate_random_number_sequence("5");
  TEST_ASSERT_NOT_NULL(sequence);

  int count = 0;
  for (char *token = strtok(sequence, " "); token != NULL;
       token = strtok(NULL, " ")) {
    int num = atoi(token);
    TEST_ASSERT_TRUE(num >= 0 && num < MAX);
    count++;
  }
  TEST_ASSERT_EQUAL(5, count);
  free(sequence);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_create_fifo);
  RUN_TEST(test_write_and_read_fifo);
  RUN_TEST(test_generate_random_number);
  RUN_TEST(test_generate_random_number_sequence);
  return UNITY_END();
}
