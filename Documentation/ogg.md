#include <ogg/ogg.h>

/*
	https://www.xiph.org/ogg/
	https://www.xiph.org/ogg/doc/rfc3533.txt
	https://www.xiph.org/ogg/doc/rfc5334.txt
*/
/*
	The Ogg bitstream format is also documented in the following IETF RFCs:
	RFC 3533 The Ogg Encapsulation Format Version 0 (IETF mirror)
	RFC 5334 Ogg Media Types (IETF mirror)
*/
/*
	stream
	packet
	page
*/
/*
	stream:
		struct:
			ogg_stream_state
		API:
			ogg_stream_init
			ogg_stream_clear
			ogg_stream_reset
			ogg_stream_destroy
*/

/*
	page:
		struct:
			ogg_packet
		API:
			ogg_page_bos
			ogg_page_eos
*/
/*
	packet:
		struct:
			ogg_packet 
		API:
			ogg_page_bos
			ogg_page_eos
*/
/*
	pack buffer:
		struct:
			oggpack_buffer
		API:
			oggpack_writeinit
			oggpack_write
			oggpack_readinit
			oggpack_read
			oggpack_reset
*/
/*
	encoding API:
		ogg_stream_packetin
		ogg_stream_pageout
*/
