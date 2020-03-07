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



#endif /* SFML_SERV_HPP_ */
