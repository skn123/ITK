#==========================================================================
#
#   Copyright NumFOCUS
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          http://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#==========================================================================*/

#
#  Example on the use of DicomImageIO for reading a single DICOM slice, rescale
#  the intensities and save it in a different file format.
#
package require InsightToolkit

set reader [ itkImageFileReaderIUC2_New ]
set writer [ itkImageFileWriterIUC2_New ]

set filter [ itkRescaleIntensityImageFilterIUC2IUC2_New ]

set dicomIO [ itkDicomImageIO_New ]

$reader     SetImageIO [ $dicomIO GetPointer ]

$filter     SetInput [ $reader  GetOutput ]
$writer     SetInput [ $filter  GetOutput ]

$filter     SetOutputMinimum    0
$filter     SetOutputMaximum  255

$reader SetFileName [lindex $argv 0]
$writer SetFileName [lindex $argv 1]

$writer Update


exit
