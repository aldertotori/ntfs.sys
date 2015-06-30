
#include "ntfs.h"

/*
typedef struct _KEY_VALUE_FULL_INFORMATION {
    ULONG   TitleIndex;
    ULONG   Type;
    ULONG   DataOffset;
    ULONG   DataLength;
    ULONG   NameLength;
    WCHAR   Name[1];            // Variable size
	//          Data[1];            // Variable size data not declared
} KEY_VALUE_FULL_INFORMATION, *PKEY_VALUE_FULL_INFORMATION;
*/

NTSTATUS NtfsQueryValueKey(IN PUNICODE_STRING				KeyName, 
						   IN PUNICODE_STRING				ValueName,
						   IN OUT ULONG						*KeyInfoSize, 
						   OUT PKEY_VALUE_FULL_INFORMATION *KeyInfo, 
						   OUT BOOLEAN*						bNeedRelease)
{
	NTSTATUS			Status;
	OBJECT_ATTRIBUTES	ObjectAttributes;
	HANDLE				Handle;
	ULONG				MemSize;
	ULONG				ResultLength;
	
	InitializeObjectAttributes(&ObjectAttributes,KeyName,OBJ_CASE_INSENSITIVE,NULL,NULL);
	Status = ZwOpenKey(&Handle,0x20019, &ObjectAttributes);
	if(NT_SUCCESS(Status))
	{
		MemSize = *KeyInfoSize;
		do
		{
			Status = ZwQueryValueKey(Handle, ValueName, KeyValueFullInformation, (PVOID)*KeyInfo, MemSize, &ResultLength);
			
			if(Status != 0x80000005)
				break;
			
			if(bNeedRelease[0])
			{
				ExFreePool(*KeyInfo);
				KeyInfoSize[0] = 0;
				KeyInfo[0] = 0;
				bNeedRelease[0] = FALSE;
			}
			
			MemSize += 256;
			
			KeyInfo[0] = (PKEY_VALUE_FULL_INFORMATION)ExAllocatePoolWithTag(PagedPool, MemSize, REG_TAG );
			
			if(!KeyInfo[0])
				return 0xC0000017;
			
			KeyInfoSize[0]  = MemSize;
			bNeedRelease[0] = TRUE;
			
		} while (TRUE);
		
		ZwClose(Handle);
		
		if(NT_SUCCESS(Status))
		{
			if(!KeyInfo[0]->NameLength)
			{
				Status = 0xC0000034;
			}	
		}
	}
	
	return Status;
}

