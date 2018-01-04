#pragma once
// MESSAGE ATTITUDE_ERR_ICV PACKING

#define MAVLINK_MSG_ID_ATTITUDE_ERR_ICV 269

MAVPACKED(
typedef struct __mavlink_attitude_err_icv_t {
 float x_err; /*< x error*/
 float y_err; /*< y error*/
 float z_err; /*< z error*/
}) mavlink_attitude_err_icv_t;

#define MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN 12
#define MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_MIN_LEN 12
#define MAVLINK_MSG_ID_269_LEN 12
#define MAVLINK_MSG_ID_269_MIN_LEN 12

#define MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_CRC 195
#define MAVLINK_MSG_ID_269_CRC 195



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ATTITUDE_ERR_ICV { \
    269, \
    "ATTITUDE_ERR_ICV", \
    3, \
    {  { "x_err", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_attitude_err_icv_t, x_err) }, \
         { "y_err", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_attitude_err_icv_t, y_err) }, \
         { "z_err", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_attitude_err_icv_t, z_err) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ATTITUDE_ERR_ICV { \
    "ATTITUDE_ERR_ICV", \
    3, \
    {  { "x_err", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_attitude_err_icv_t, x_err) }, \
         { "y_err", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_attitude_err_icv_t, y_err) }, \
         { "z_err", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_attitude_err_icv_t, z_err) }, \
         } \
}
#endif

/**
 * @brief Pack a attitude_err_icv message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param x_err x error
 * @param y_err y error
 * @param z_err z error
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_attitude_err_icv_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float x_err, float y_err, float z_err)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN];
    _mav_put_float(buf, 0, x_err);
    _mav_put_float(buf, 4, y_err);
    _mav_put_float(buf, 8, z_err);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN);
#else
    mavlink_attitude_err_icv_t packet;
    packet.x_err = x_err;
    packet.y_err = y_err;
    packet.z_err = z_err;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ATTITUDE_ERR_ICV;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_MIN_LEN, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_CRC);
}

/**
 * @brief Pack a attitude_err_icv message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param x_err x error
 * @param y_err y error
 * @param z_err z error
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_attitude_err_icv_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float x_err,float y_err,float z_err)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN];
    _mav_put_float(buf, 0, x_err);
    _mav_put_float(buf, 4, y_err);
    _mav_put_float(buf, 8, z_err);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN);
#else
    mavlink_attitude_err_icv_t packet;
    packet.x_err = x_err;
    packet.y_err = y_err;
    packet.z_err = z_err;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ATTITUDE_ERR_ICV;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_MIN_LEN, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_CRC);
}

/**
 * @brief Encode a attitude_err_icv struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param attitude_err_icv C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_attitude_err_icv_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_attitude_err_icv_t* attitude_err_icv)
{
    return mavlink_msg_attitude_err_icv_pack(system_id, component_id, msg, attitude_err_icv->x_err, attitude_err_icv->y_err, attitude_err_icv->z_err);
}

/**
 * @brief Encode a attitude_err_icv struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param attitude_err_icv C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_attitude_err_icv_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_attitude_err_icv_t* attitude_err_icv)
{
    return mavlink_msg_attitude_err_icv_pack_chan(system_id, component_id, chan, msg, attitude_err_icv->x_err, attitude_err_icv->y_err, attitude_err_icv->z_err);
}

/**
 * @brief Send a attitude_err_icv message
 * @param chan MAVLink channel to send the message
 *
 * @param x_err x error
 * @param y_err y error
 * @param z_err z error
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_attitude_err_icv_send(mavlink_channel_t chan, float x_err, float y_err, float z_err)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN];
    _mav_put_float(buf, 0, x_err);
    _mav_put_float(buf, 4, y_err);
    _mav_put_float(buf, 8, z_err);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV, buf, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_MIN_LEN, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_CRC);
#else
    mavlink_attitude_err_icv_t packet;
    packet.x_err = x_err;
    packet.y_err = y_err;
    packet.z_err = z_err;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV, (const char *)&packet, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_MIN_LEN, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_CRC);
#endif
}

/**
 * @brief Send a attitude_err_icv message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_attitude_err_icv_send_struct(mavlink_channel_t chan, const mavlink_attitude_err_icv_t* attitude_err_icv)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_attitude_err_icv_send(chan, attitude_err_icv->x_err, attitude_err_icv->y_err, attitude_err_icv->z_err);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV, (const char *)attitude_err_icv, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_MIN_LEN, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_CRC);
#endif
}

#if MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_attitude_err_icv_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float x_err, float y_err, float z_err)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, x_err);
    _mav_put_float(buf, 4, y_err);
    _mav_put_float(buf, 8, z_err);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV, buf, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_MIN_LEN, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_CRC);
#else
    mavlink_attitude_err_icv_t *packet = (mavlink_attitude_err_icv_t *)msgbuf;
    packet->x_err = x_err;
    packet->y_err = y_err;
    packet->z_err = z_err;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV, (const char *)packet, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_MIN_LEN, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_CRC);
#endif
}
#endif

#endif

// MESSAGE ATTITUDE_ERR_ICV UNPACKING


/**
 * @brief Get field x_err from attitude_err_icv message
 *
 * @return x error
 */
static inline float mavlink_msg_attitude_err_icv_get_x_err(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field y_err from attitude_err_icv message
 *
 * @return y error
 */
static inline float mavlink_msg_attitude_err_icv_get_y_err(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field z_err from attitude_err_icv message
 *
 * @return z error
 */
static inline float mavlink_msg_attitude_err_icv_get_z_err(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a attitude_err_icv message into a struct
 *
 * @param msg The message to decode
 * @param attitude_err_icv C-struct to decode the message contents into
 */
static inline void mavlink_msg_attitude_err_icv_decode(const mavlink_message_t* msg, mavlink_attitude_err_icv_t* attitude_err_icv)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    attitude_err_icv->x_err = mavlink_msg_attitude_err_icv_get_x_err(msg);
    attitude_err_icv->y_err = mavlink_msg_attitude_err_icv_get_y_err(msg);
    attitude_err_icv->z_err = mavlink_msg_attitude_err_icv_get_z_err(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN? msg->len : MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN;
        memset(attitude_err_icv, 0, MAVLINK_MSG_ID_ATTITUDE_ERR_ICV_LEN);
    memcpy(attitude_err_icv, _MAV_PAYLOAD(msg), len);
#endif
}
