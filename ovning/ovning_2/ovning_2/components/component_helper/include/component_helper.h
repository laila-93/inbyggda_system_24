#ifndef COMPONENT_HELPER_H
#define COMPONENET_HELPER_H 


void run (){                                             // definition​

  for (int i = 0; i < 5; i++){
 int number = getNumber( i );
printf(“%d\n”, number);
}

}



int getNumber(int pos){                   // definition​
int array[5] = {1, 2, 3, 4, 5}; 

  return array[pos];

}


#endif 