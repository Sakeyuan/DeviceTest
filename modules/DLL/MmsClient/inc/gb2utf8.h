
#define NOT_SUPPORTED	-1
#define HZ_NUM			6763
#define SYM_NUM			717
#define CODE_NUM		(HZ_NUM+SYM_NUM)

// 屏蔽某项可节省部分内存
#if defined(_WIN32)
  #define UCS2TOGB_ENABLE       // 支持UCS2转GB
#endif
  #define GBTOUCS2_ENABLE       // 支持GB转UCS2

#ifdef __cplusplus
extern "C" {
#endif

#if defined(GBTOUCS2_ENABLE)
int gb2uni( const unsigned char *gbstr, unsigned short *unibuf, int buflen );
#endif
#if defined(UCS2TOGB_ENABLE)
int uni2gb( const unsigned short *unistr, unsigned char *gbbuf, int buflen );
#endif

int ucs2ToUtf8(const unsigned short *ucs, unsigned char *cbuf, int cbuf_len);
int utf8ToUcs2(const unsigned char *s, unsigned short *wbuf, int wbuf_len);

#ifdef __cplusplus
}
#endif



