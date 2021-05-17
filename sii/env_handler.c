#include <stdlib.h>
#include <stdio.h>

int get_env_data(void *IP_TARGET, void *PORT_TARGET, void *IP_SOURCE, void *PORT_SOURCE){
    if (getenv("IP_TARGET")){
		printf("IP_TARGET=%s\n",getenv("IP_TARGET") );
        sscanf(getenv("IP_TARGET"),"%s",IP_TARGET);
    } else printf("IP_TARGET not found\n"); 

    if (getenv("PORT_TARGET")){
		printf("PORT_TARGET=%s\n",getenv("PORT_TARGET")); 
        sscanf(getenv("PORT_TARGET"),"%d",PORT_TARGET);
    } else printf("PORT_TARGET not found\n");

    if (getenv("IP_SOURCE")){
		printf("IP_SOURCE=%s\n",getenv("IP_SOURCE") );
        sscanf(getenv("IP_SOURCE"),"%s",IP_SOURCE);
    } else printf("IP_SOURCE not found\n"); 

    if (getenv("PORT_SOURCE")){
        printf("PORT_SOURCE=%s\n",getenv("PORT_SOURCE"));
        sscanf(getenv("PORT_SOURCE"),"%d",PORT_SOURCE);
    } else printf("PORT_SOURCE not found");
    printf("\n\n");
    
    return 0;
}