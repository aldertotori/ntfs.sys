

extern ULONG		NtfsLastAccess;

extern ULONG		dword_2FF54		;

extern PVOID		NtfsReserved1	;

extern PVOID		NtfsReserved2	;

extern PVOID		NtfsReserved3	;

extern KEVENT		NtfsEncryptionPendingEvent;

extern KMUTANT		StreamFileCreationMutex;

extern ULONG		NtfsMcbCurrentLevel;

extern LIST_ENTRY	NtfsMcbLruQueue;

extern ULONG		dword_2FFA4;

extern ULONG		dword_2FFA8;

extern KEVENT		Event_2FFAC;

extern ULONG		NtfsMcbFastMutex ;

extern ULONG		NtfsMcbHighWaterMark ;

extern ULONG		NtfsMcbLowWaterMark	 ;

extern PVOID		dword_300A8 ;

extern USHORT		word_30188 ;

extern BOOLEAN		NtfsMcbCleanupInProgress;

extern FAST_IO_DISPATCH	NtfsFastIoDispatch;

extern ULONG	NtfsZeroExtendedInfo[12];

extern ULONG			NtfsData[126];

extern ERESOURCE		Resource;			// 

extern KEVENT			Event_301B0;
