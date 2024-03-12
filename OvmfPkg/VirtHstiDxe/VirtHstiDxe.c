/** @file
  This file contains DXE driver for publishing empty HSTI table

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
Copyright (c) 2024, Red Hat. Inc

SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <IndustryStandard/Hsti.h>
#include <Library/HstiLib.h>

#define HSTI_PLATFORM_NAME          L"Intel(R) 9-Series v1"
#define HSTI_SECURITY_FEATURE_SIZE  1

ADAPTER_INFO_PLATFORM_SECURITY  mHstiBase = {
  PLATFORM_SECURITY_VERSION_VNEXTCS,
  PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
  { HSTI_PLATFORM_NAME },
  HSTI_SECURITY_FEATURE_SIZE,
};

/**
  The driver's entry point.

  @param[in] ImageHandle  The firmware allocated handle for the EFI image.
  @param[in] SystemTable  A pointer to the EFI System Table.

  @retval EFI_SUCCESS     The entry point is executed successfully.
  @retval other           Some error occurs when executing this entry point.
**/
EFI_STATUS
EFIAPI
VirtHstiDxeEntrypoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status;

  // Allocate memory for HSTI struct
  // 3 * sizeof (UINT8) * HSTI_SECURITY_FEATURE_SIZE is for the 3 arrays
  //   UINT8   SecurityFeaturesRequired[];
  //   UINT8   SecurityFeaturesImplemented[];
  //   UINT8   SecurityFeaturesVerified[];
  // sizeof (CHAR16) is for the NULL terminator of ErrorString
  //   CHAR16 ErrorString[]
  UINTN  HstiSize = sizeof (ADAPTER_INFO_PLATFORM_SECURITY) +
                    3 * sizeof (UINT8) * HSTI_SECURITY_FEATURE_SIZE +
                    sizeof (CHAR16);
  VOID  *HstiStruct = AllocateZeroPool (HstiSize);

  if (HstiStruct == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  CopyMem (HstiStruct, &mHstiBase, sizeof (ADAPTER_INFO_PLATFORM_SECURITY));

  Status = HstiLibSetTable (HstiStruct, HstiSize);
  if (EFI_ERROR (Status)) {
    if (Status != EFI_ALREADY_STARTED) {
      ASSERT_EFI_ERROR (Status);
    }
  }

  return EFI_SUCCESS;
}
