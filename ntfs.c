#include "ntfs.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject,PUNICODE_STRING RegistryPath);
VOID DriverUnload(PDRIVER_OBJECT DriverObject);

#ifdef ALLOC_PRAGMA
#pragma alloc_text (INIT, DriverEntry)
#pragma alloc_text (PAGE, DriverUnload)
#endif


NTSTATUS  DriverEntry(PDRIVER_OBJECT DriverObject,PUNICODE_STRING RegistryPath)
{
	NTSTATUS			Status = STATUS_SUCCESS;
	UNICODE_STRING		DeviceName;
	PDEVICE_OBJECT		DeviceObject;
	UNICODE_STRING		ValueName;
	UNICODE_STRING		KeyName;
	MM_SYSTEMSIZE		SysSize;

	PAGED_CODE();

	NtfsLastAccess  = 0x61C46800;
	dword_2FF54		= 8;

	NtfsReserved1   = ExAllocatePoolWithTag(NonPagedPool,0x10000,POOL_TAG);

	if(!NtfsReserved1)
	{
		return 0xC000009A;
	}

	NtfsReserved2   = ExAllocatePoolWithTag(NonPagedPool,0x10000,POOL_TAG);

	if(!NtfsReserved2)
	{
		ExFreePool(NtfsReserved1);
		return 0xC000009A;
	}

	NtfsReserved3   = ExAllocatePoolWithTag(NonPagedPool,0x10000,POOL_TAG);

	if(!NtfsReserved3)
	{
		ExFreePool(NtfsReserved1);
		ExFreePool(NtfsReserved2);
		return 0xC000009A;
	}

	RtlInitUnicodeString(&DeviceName,NT_DEVICE_NAME);

	Status = IoCreateDevice(DriverObject,
							0,
							&DeviceName,
							FILE_DEVICE_DISK_FILE_SYSTEM,
							0,
							FALSE,
							&DeviceObject);
	if(!NT_SUCCESS(Status))
	{
		ExFreePool(NtfsReserved1);
		ExFreePool(NtfsReserved2);
		ExFreePool(NtfsReserved3);
		return Status;
	}

	DriverObject->MajorFunction[IRP_MJ_LOCK_CONTROL] = NtfsFsdLockControl;
	DriverObject->MajorFunction[IRP_MJ_DIRECTORY_CONTROL] = NtfsFsdDirectoryControl;
	DriverObject->MajorFunction[IRP_MJ_SET_INFORMATION] = NtfsFsdSetInformation;
	DriverObject->MajorFunction[IRP_MJ_CREATE] = NtfsFsdCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = NtfsFsdClose;
	DriverObject->MajorFunction[IRP_MJ_READ] = NtfsFsdRead;
	DriverObject->MajorFunction[IRP_MJ_WRITE] = NtfsFsdWrite;
	DriverObject->MajorFunction[IRP_MJ_FLUSH_BUFFERS] = NtfsFsdFlushBuffers;
	DriverObject->MajorFunction[IRP_MJ_FILE_SYSTEM_CONTROL] = NtfsFsdFileSystemControl;
	DriverObject->MajorFunction[IRP_MJ_CLEANUP] = NtfsFsdCleanup;
	DriverObject->MajorFunction[IRP_MJ_SHUTDOWN] = NtfsFsdShutdown;
	DriverObject->MajorFunction[IRP_MJ_PNP] = NtfsFsdPnp;
	
	DriverObject->MajorFunction[IRP_MJ_QUERY_INFORMATION] = NtfsFsdDispatchWait;
	DriverObject->MajorFunction[IRP_MJ_SET_QUOTA] = NtfsFsdDispatchWait;
	DriverObject->MajorFunction[IRP_MJ_QUERY_QUOTA] = NtfsFsdDispatchWait;
	DriverObject->MajorFunction[IRP_MJ_SET_EA] = NtfsFsdDispatchWait;
	DriverObject->MajorFunction[IRP_MJ_QUERY_EA] = NtfsFsdDispatchWait;
	DriverObject->MajorFunction[IRP_MJ_SET_VOLUME_INFORMATION] = NtfsFsdDispatch;
	DriverObject->MajorFunction[IRP_MJ_QUERY_VOLUME_INFORMATION] = NtfsFsdDispatch;
	DriverObject->MajorFunction[IRP_MJ_SET_SECURITY] = NtfsFsdDispatch;
	DriverObject->MajorFunction[IRP_MJ_QUERY_SECURITY] = NtfsFsdDispatch;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = NtfsFsdDispatch;

	DriverObject->FastIoDispatch = (PFAST_IO_DISPATCH)&NtfsFastIoDispatch;

	NtfsInitializeNtfsData(DriverObject);

	if ( NtfsRunningOnWhat(512, 1) )
		word_30188 |= 0x200;

	KeInitializeMutant(&StreamFileCreationMutex, 0);

	KeInitializeEvent(&NtfsEncryptionPendingEvent, NotificationEvent, TRUE);
	NtfsMcbFastMutex = 1;
	dword_2FFA4 = 0;
	dword_2FFA8 = 0;
	KeInitializeEvent(&Event_2FFAC, SynchronizationEvent, 0);
	
	InitializeListHead(&NtfsMcbLruQueue);
	NtfsMcbCleanupInProgress = FALSE;
	NtfsMcbCurrentLevel	= 0;

	switch(MmQuerySystemSize())
	{
	case MmSmallSystem:
		NtfsMcbHighWaterMark = 1600;
		NtfsMcbLowWaterMark	 = 800;
		break;
	case MmMediumSystem:
		NtfsMcbHighWaterMark = 4000;
		NtfsMcbLowWaterMark	 = 2000;
		break;
	
	default:
		NtfsMcbHighWaterMark = 16000;
		NtfsMcbLowWaterMark	 = 8000;
		break;
	}

	if ( NtfsRunningOnWhat(0x80, 3) || NtfsRunningOnWhat(0x80, 2) )
	{
		NtfsMcbHighWaterMark *= 2;
		NtfsMcbLowWaterMark *= 2;
	}

	dword_300A8 = ExAllocatePoolWithTag(NonPagedPool,0x300A0,RES_TAG);
	if(dword_300A8)
	{
		RtlZeroMemory(dword_300A8,0x300A0);
		RtlZeroMemory(&NtfsZeroExtendedInfo,12*sizeof(ULONG));
		IoRegisterFileSystem(DeviceObject);
		LfsInitializeLogFileService();
		RtlInitUnicodeString(&KeyName,L"\\Registry\\Machine\\System\\Setup");
		RtlInitUnicodeString(&ValueName,L"SystemSetupInProgress");
		
		// ??
		Status = NtfsQueryValueKey(&KeyName,&ValueName);
		if(NT_SUCCESS(Status))
		{



		}

	}
	else
	{
		KeBugCheck(NTFS_FILE_SYSTEM);
	}

	return Status;
}

VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	PAGED_CODE();
	
}

