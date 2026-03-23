// fifo page replacement algorithm
#include <stdio.h>
#include <stdbool.h>

// returns true if array has val; false otherwise
bool contains(int arr[], int size, int val) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == val) return true;
  }
  return false;
}

int main() {
  int ref_size, frame_size;
  printf("Enter number of frames: ");
  scanf("%d", &frame_size);
  printf("Enter length of reference string: ");
  scanf("%d", &ref_size);

  int ref[ref_size], frames[frame_size], current_frame = -1, hits = 0;
  for(int i = 0; i < frame_size; i++) frames[i] = -1;

  printf("Enter reference string\n");
  for (int i = 0; i < ref_size; i++) {
    scanf("%d", &ref[i]);
  }

  printf("req\tstatus     \tframes\n");
  for (int i = 0; i < ref_size; i++) {
    printf("%3d\t", ref[i]);
    if (contains(frames, frame_size, ref[i])) { // page hit
      printf("hit       \t");
      hits++;
    } else { // page fault
      printf("page-fault\t");
      current_frame = (current_frame + 1) % frame_size; // circular array implementation
      frames[current_frame] = ref[i];
    }
    for (int j = 0; j < frame_size; j++) {
      if (frames[j] < 0) printf("_, ");
      else printf("%d, ", frames[j]);
    }
    printf("\n");
  }
  printf("\nnumber of page hits = %d\n", hits);
  printf("number of page faults = %d\n", ref_size - hits);

  return 0;
}
 /*
OUTPUT:
Enter number of frames: 3
Enter length of reference string: 7
Enter reference string
1
3
0
3
5
6
3
req	status     	frames
  1	page-fault	1, _, _, 
  3	page-fault	1, 3, _, 
  0	page-fault	1, 3, 0, 
  3	hit       	1, 3, 0, 
  5	page-fault	5, 3, 0, 
  6	page-fault	5, 6, 0, 
  3	page-fault	5, 6, 3, 

number of page hits = 1
number of page faults = 6
 */
