#pragma once
// MESSAGE COORD_ICV PACKING

#define MAVLINK_MSG_ID_COORD_ICV 269

MAVPACKED(
typedef struct __mavlink_coord_icv_t {
 uint16_t x; /*< x*/
 uint16_t y; /*< y*/
}) mavlink_coord_icv_t;

#define MAVLINK_MSG_ID_COORD_ICV_LEN 4
#define MAVLINK_MSG_ID_COORD_ICV_MIN_LEN 4
#define MAVLINK_MSG_ID_269_LEN 4
#define MAVLINK_MSG_ID_269_MIN_LEN 4

#define MAVLINK_MSG_ID_COORD_ICV_CRC 147
#define MAVLINK_MSG_ID_269_CRC 147



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_COORD_ICV { \
    269, \
    "COORD_ICV", \
    2, \
    {  { "x", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_coord_icv_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_coord_icv_t, y) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_COORD_ICV { \
    "COORD_ICV", \
    2, \
    {  { "x", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_coord_icv_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_coord_icv_t, y) }, \
         } \
}
#endif

/**
 * @brief Pack a coord_icv message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param x x
 * @param y y
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_coord_icv_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t x, uint16_t y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COORD_ICV_LEN];
    _mav_put_uint16_t(buf, 0, x);
    _mav_put_uint16_t(buf, 2, y);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COORD_ICV_LEN);
#else
    mavlink_coord_icv_t packet;
    packet.x = x;
    packet.y = y;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COORD_ICV_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COORD_ICV;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_COORD_ICV_MIN_LEN, MAVLINK_MSG_ID_COORD_ICV_LEN, MAVLINK_MSG_ID_COORD_ICV_CRC);
}

/**
 * @brief Pack a coord_icv message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param x x
 * @param y y
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_coord_icv_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t x,uint16_t y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COORD_ICV_LEN];
    _mav_put_uint16_t(buf, 0, x);
    _mav_put_uint16_t(buf, 2, y);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COORD_ICV_LEN);
#else
    mavlink_coord_icv_t packet;
    packet.x = x;
    packet.y = y;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COORD_ICV_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COORD_ICV;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_COORD_ICV_MIN_LEN, MAVLINK_MSG_ID_COORD_ICV_LEN, MAVLINK_MSG_ID_COORD_ICV_CRC);
}

/**
 * @brief Encode a coord_icv struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param coord_icv C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_coord_icv_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_coord_icv_t* coord_icv)
{
    return mavlink_msg_coord_icv_pack(system_id, component_id, msg, coord_icv->x, coord_icv->y);
}

/**
 * @brief Encode a coord_icv struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param coord_icv C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_coord_icv_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_coord_icv_t* coord_icv)
{
    return mavlink_msg_coord_icv_pack_chan(system_id, component_id, chan, msg, coord_icv->x, coord_icv->y);
}

/**
 * @brief Send a coord_icv message
 * @param chan MAVLink channel to send the message
 *
 * @param x x
 * @param y y
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_coord_icv_send(mavlink_channel_t chan, uint16_t x, uint16_t y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COORD_ICV_LEN];
    _mav_put_uint16_t(buf, 0, x);
    _mav_put_uint16_t(buf, 2, y);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COORD_ICV, buf, MAVLINK_MSG_ID_COORD_ICV_MIN_LEN, MAVLINK_MSG_ID_COORD_ICV_LEN, MAVLINK_MSG_ID_COORD_ICV_CRC);
#else
    mavlink_coord_icv_t packet;
    packet.x = x;
    packet.y = y;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COORD_ICV, (const char *)&packet, MAVLINK_MSG_ID_COORD_ICV_MIN_LEN, MAVLINK_MSG_ID_COORD_ICV_LEN, MAVLINK_MSG_ID_COORD_ICV_CRC);
#endif
}

/**
 * @brief Send a coord_icv message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_coord_icv_send_struct(mavlink_channel_t chan, const mavlink_coord_icv_t* coord_icv)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_coord_icv_send(chan, coord_icv->x, coord_icv->y);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COORD_ICV, (const char *)coord_icv, MAVLINK_MSG_ID_COORD_ICV_MIN_LEN, MAVLINK_MSG_ID_COORD_ICV_LEN, MAVLINK_MSG_ID_COORD_ICV_CRC);
#endif
}

#if MAVLINK_MSG_ID_COORD_ICV_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_coord_icv_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t x, uint16_t y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, x);
    _mav_put_uint16_t(buf, 2, y);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COORD_ICV, buf, MAVLINK_MSG_ID_COORD_ICV_MIN_LEN, MAVLINK_MSG_ID_COORD_ICV_LEN, MAVLINK_MSG_ID_COORD_ICV_CRC);
#else
    mavlink_coord_icv_t *packet = (mavlink_coord_icv_t *)msgbuf;
    packet->x = x;
    packet->y = y;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COORD_ICV, (const char *)packet, MAVLINK_MSG_ID_COORD_ICV_MIN_LEN, MAVLINK_MSG_ID_COORD_ICV_LEN, MAVLINK_MSG_ID_COORD_ICV_CRC);
#endif
}
#endif

#endif

// MESSAGE COORD_ICV UNPACKING


/**
 * @brief Get field x from coord_icv message
 *
 * @return x
 */
static inline uint16_t mavlink_msg_coord_icv_get_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field y from coord_icv message
 *
 * @return y
 */
static inline uint16_t mavlink_msg_coord_icv_get_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Decode a coord_icv message into a struct
 *
 * @param msg The message to decode
 * @param coord_icv C-struct to decode the message contents into
 */
static inline void mavlink_msg_coord_icv_decode(const mavlink_message_t* msg, mavlink_coord_icv_t* coord_icv)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    coord_icv->x = mavlink_msg_coord_icv_get_x(msg);
    coord_icv->y = mavlink_msg_coord_icv_get_y(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_COORD_ICV_LEN? msg->len : MAVLINK_MSG_ID_COORD_ICV_LEN;
        memset(coord_icv, 0, MAVLINK_MSG_ID_COORD_ICV_LEN);
    memcpy(coord_icv, _MAV_PAYLOAD(msg), len);
#endif
}
