/*
 * Copyright (c) University of British Columbia, 1984
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
 *
 * %sccs.include.redist.c%
 *
 *	@(#)x25.h	7.2 (Berkeley) %G%
 */

#ifdef KERNEL
#define PRC_IFUP	3
#define PRC_LINKUP	4
#define PRC_LINKDOWN	5
#define PRC_LINKRESET	6
#define PRC_LINKDONTCOPY	7
#endif

#define CCITTPROTO_HDLC		1
#define CCITTPROTO_X25		2	/* packet level protocol */
#define IEEEPROTO_802LLC	3	/* doesn't belong here */

#define HDLCPROTO_LAP		1
#define HDLCPROTO_LAPB		2
#define HDLCPROTO_UNSET		3
#define HDLCPROTO_LAPD		4

/*
 *  X.25 Socket address structure.  It contains the  X.121 or variation of
 *  X.121, facilities information, higher level protocol value (first four
 *  bytes of the User Data field), and the last  12 characters of the User
 *  Data field.
 */

struct x25_sockaddr {		/* obsolete - use sockaddr_x25 */
    short  xaddr_len;		/* Length of xaddr_addr.		*/
    u_char xaddr_addr[15];	/* Network dependent or X.121 address.	*/
    u_char xaddr_facilities;	/* Facilities information.		*/
#define XS_REVERSE_CHARGE	0x01
#define XS_HIPRIO		0x02
    u_char xaddr_proto[4];	/* Protocol ID (4 bytes of user data).	*/
    u_char xaddr_userdata[12];	/* Remaining User data field.		*/
};

/*
 * network configuration info
 * this structure must be 16 bytes long
 */

struct	x25config {
	u_short	xc_family;	/* always AF_CCITT */
	u_short	xc_net;		/* network id (usually a dnic) */
	char	xc_ntnlen;
	char	xc_ntn[5];	/* network specific address (in bcd) */
	/* link level parameters */
	u_short	xc_lproto:4,	/* link level protocol eg. CCITTPROTO_HDLC */
		xc_lptype:4,	/* protocol type eg. HDLCPROTO_LAPB */
		xc_lwsize:5,	/* link level window size */
		xc_ltrace:1,	/* link level tracing flag */
		xc_rsvd1:2;	/* for use by other link-level protocols */
	/* packet level parameters */
	u_short	xc_pwsize:3,	/* default window size */
		xc_psize:4,	/* default packet size 7=128, 8=256, ... */
		xc_type:3,	/* network type */
#define X25_1976	0
#define X25_1980	1
#define X25_1984	2
#define X25_DDN		3
#define X25_BASIC	4
		xc_ptrace:1,	/* packet level tracing flag */
		xc_rsvd2:5;
	u_char	xc_maxlcn;	/* max logical channels */
	u_char	xc_rsvd3;
};

/*
 *  X.25 Socket address structure.  It contains the network id, X.121
 *  address, facilities information, higher level protocol value (first four
 *  bytes of the User Data field), and up to 12 characters of User Data.
 */

struct	sockaddr_x25 {
	u_char	x25_len;
	u_char	x25_family;	/* must be AF_CCITT */
	short	x25_net;	/* network id code (usually a dnic) */
	struct	x25opts {
		char	op_flags;	/* miscellaneous options */
#define X25_REVERSE_CHARGE	0x01	/* remote DTE pays for call */
#define X25_DBIT		0x02	/* not yet supported */
#define X25_MQBIT		0x04	/* prepend M&Q bit status byte to packet data */
#define X25_OLDSOCKADDR		0x08	/* uses old sockaddr structure */
		char	op_psize;	/* requested packet size */
#define X25_PS128		7
#define X25_PS256		8
#define X25_PS512		9
		char	op_wsize;	/* window size (1 .. 7) */
		char	op_speed;	/* throughput class */
	} x25_opts;
	char	x25_addr[16];	/* X.121 address (null terminated) */
	short	x25_udlen;	/* user data field length */
	char	x25_udata[16];	/* user data field */
};
