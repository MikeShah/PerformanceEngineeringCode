// collide.c

// Checks if a collision occurred
if( sqrt(sqr(x1-x2) + sqr(y1-y2)) < (r1 + r2)){
    return 1;
}else{
    return 0;
}


// versus

if(abs(x1-x2) > r1 +r2){
    return 0; // fast exit
}
if(abs(y1-y2) > r1 +r2){
    return 0; // fast exit
}
if( sqrt(sqr(x1-x2) + sqr(y1-y2)) < (r1 + r2)){
    return 1;
}else{
    return 0;
}


