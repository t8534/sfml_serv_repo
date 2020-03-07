/*
 * sfml_serv.hpp
 *
 *      Author: LiberdaA
 */

#ifndef SFML_SERV_HPP_
#define SFML_SERV_HPP_

#include <pthread.h>

extern pthread_mutex_t gpsmsg_mutex;
extern pthread_mutex_t condition_mutex;
extern pthread_cond_t  condition_cond;


#define GPSDEV_BUFF_LEN	128


#if 0
#include <pthread.h>


pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;
#endif


#endif /* SFML_SERV_HPP_ */
