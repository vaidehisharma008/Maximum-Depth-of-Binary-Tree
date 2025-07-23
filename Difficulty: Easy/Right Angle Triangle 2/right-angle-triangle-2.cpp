void triangle(int s) {
    // Write your code here
    for(int i = 0; i < s; i++){
        for(int j = 0; j <= i; j++){
            if((j == 0) || (j == i) || i==(s-1)){
                cout<<"*"<<" ";
            }else{
                cout<<"  ";
            }
        }
        cout<<endl;
    }
}