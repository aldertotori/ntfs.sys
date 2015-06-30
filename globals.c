
#include "ntfs.h"

ULONG		NtfsLastAccess	= 0;

ULONG		dword_2FF54		= 0;

PVOID		NtfsReserved1	= NULL;

PVOID		NtfsReserved2	= NULL;

PVOID		NtfsReserved3	= NULL;

KEVENT		NtfsEncryptionPendingEvent;

KMUTANT		StreamFileCreationMutex;

ULONG		NtfsMcbCurrentLevel;

LIST_ENTRY	NtfsMcbLruQueue;

ULONG		dword_2FFA4;

ULONG		dword_2FFA8;

KEVENT		Event_2FFAC;

ULONG		NtfsMcbFastMutex = 0;

ULONG		NtfsMcbHighWaterMark = 0;

ULONG		NtfsMcbLowWaterMark	 = 0;

PVOID		dword_300A8 = NULL;

USHORT		word_30188 = 0;

BOOLEAN		NtfsMcbCleanupInProgress = FALSE;

ULONG			NtfsData[126];

ERESOURCE		Resource;			// 

KEVENT			Event_301B0;

FAST_IO_DISPATCH	NtfsFastIoDispatch = {
	sizeof(FAST_IO_DISPATCH),
		
		
		
};

ULONG	NtfsZeroExtendedInfo[12];
