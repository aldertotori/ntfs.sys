#include <ntddk.h>
#include "globals.h"

#define	POOL_TAG		'Ntf0'
#define RES_TAG			'Ntfr'
#define REG_TAG			'Ntfx'

#define NT_DEVICE_NAME			L"\\Ntfs"

typedef struct _DEVICE_EXTENSION
{
	PDEVICE_OBJECT       Device;
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;

///////////////////////////////////////////////////////////////////////////////////////////

#if _MSC_VER < 1200

#define ExFreePoolWithTag(x,z)  ExFreePool(x)


#endif


#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
KeInitializeMutant (
					OUT PRKMUTANT Mutant,
					IN BOOLEAN InitialOwner
					);
#endif

NTKERNELAPI
NTSTATUS 
IoRegisterFileSystem(PDEVICE_OBJECT);

//////////////////////////////////////////////////////////////////////////////////
//
//
NTSTATUS NtfsQueryValueKey(IN PUNICODE_STRING				KeyName, 
						   IN PUNICODE_STRING				ValueName,
						   IN OUT ULONG						*KeyInfoSize, 
						   OUT PKEY_VALUE_FULL_INFORMATION *KeyInfo, 
						   OUT BOOLEAN*						bNeedRelease);

VOID NtfsInitializeNtfsData(PDRIVER_OBJECT DriverObject);

VOID LfsInitializeLogFileService();

BOOLEAN NtfsRunningOnWhat(ULONG unk1,ULONG u2);

//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
NTSTATUS NtfsFsdLockControl(PDEVICE_OBJECT DeviceObject,PIRP Irp);

NTSTATUS NtfsFsdDirectoryControl(PDEVICE_OBJECT DeviceObject,PIRP Irp);

NTSTATUS NtfsFsdSetInformation(PDEVICE_OBJECT DeviceObject,PIRP Irp);

NTSTATUS NtfsFsdCreate(PDEVICE_OBJECT DeviceObject,PIRP Irp);

NTSTATUS NtfsFsdClose(PDEVICE_OBJECT DeviceObject,PIRP Irp);

NTSTATUS NtfsFsdRead(PDEVICE_OBJECT DeviceObject,PIRP Irp);

NTSTATUS NtfsFsdWrite(PDEVICE_OBJECT DeviceObject,PIRP Irp);

NTSTATUS NtfsFsdFlushBuffers(PDEVICE_OBJECT DeviceObject,PIRP Irp);

NTSTATUS NtfsFsdFileSystemControl(PDEVICE_OBJECT DeviceObject,PIRP Irp);

NTSTATUS NtfsFsdCleanup(PDEVICE_OBJECT DeviceObject,PIRP Irp);

NTSTATUS NtfsFsdShutdown(PDEVICE_OBJECT DeviceObject,PIRP Irp);

NTSTATUS NtfsFsdPnp(PDEVICE_OBJECT DeviceObject,PIRP Irp);

NTSTATUS NtfsFsdDispatchWait(PDEVICE_OBJECT DeviceObject,PIRP Irp);

NTSTATUS NtfsFsdDispatch(PDEVICE_OBJECT DeviceObject,PIRP Irp);

