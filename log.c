
#include "ntfs.h"


VOID LfsInitializeLogFileService()
{



}

VOID
NtfsFspClose(IN PVOID Parameter)
{

}

VOID NtfsInitializeNtfsData()
{
	PACL						Dacl;
	PSID						Sid;
	SID_IDENTIFIER_AUTHORITY	IdentifierAuthority;
	NTSTATUS					Status;

	WORK_QUEUE_ITEM	WorkerItem;

	ExInitializeWorkItem(&WorkerItem,NtfsFspClose,NULL);

	ExInitializeResourceLite(&Resource);

	KeInitializeEvent(&Event_301B0, SynchronizationEvent, FALSE);



}