#ifndef __ptbl_vsnprintf_h__
#define __ptbl_vsnprintf_h__

/* Windows�Ǥ�vsnprintf()�Ȥ��ƻȤ������define */
/* Windows�Ǥ�vsnprintf()��Ƭ�˥�������С����դ�!!! */
#if defined _WIN32
# define vsnprintf(buf,len,fmt,ap) _vsnprintf(buf,len,fmt,ap)
#endif

#endif /* !__ptbl_vsnprintf_h__ */
