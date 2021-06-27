
#if !defined(PACKET_DEF_H)

#define PACKET_DEF_H

#include <stdbool.h>
#include <stdint.h>




typedef enum
{
	RSP_RSP_ACK = 0x30,
	RSP_RSP_NACK = 0x31,
} rsp_rsp_e;


typedef struct
{
	union
	{

		struct
		{
			uint8_t				start_code[2];
			uint16_t			dev_id; // fixed at 0x0001
			union
			{
				uint32_t		cmd_input_param;
				union
				{
					uint32_t	rsp_output_param;
					uint32_t	rsp_error_code;
				};
			};
			union
			{
				uint16_t		cmd_code;
				uint16_t		rsp_rsp;
			};
			uint16_t			check_sum;
		};
		uint8_t 				flat_data[12];
	};
} pkt_t;
typedef pkt_t *p_packet_handle_t;


/*
typedef struct
{
	p_packet_handle_t p_pkt;
} packet_ptr_t;
*/

typedef enum
{
	PKT_SRC_DST_SNS_TX,
	PKT_SRC_DST_SNS_RX,
} pkt_src_dst_t;




typedef struct
{
	uint8_t  	start_code_1;
	uint8_t 	start_code_2;
	uint16_t    dev_id;
	uint32_t    input_parameter;
	union
	{
		uint16_t    cmd_code;
		uint16_t    rsp;
	};
	uint16_t    check_sum; // sum of offset[0] + ... + offset[9] = check sum
	//uint32_t    check_sum; // sum of offset[0] + ... + offset[9] = check sum
} gt521fx_pkt_t;


typedef struct
{
	union
	{
		gt521fx_pkt_t pkt;
		uint8_t flat_data[sizeof(gt521fx_pkt_t)];
	};
} gt521fx_pkt_u;


#endif
