/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkImageRandomIteratorWithIndex.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkImageRandomIteratorWithIndex_h
#define __itkImageRandomIteratorWithIndex_h

#include "itkImageIteratorWithIndex.h"

namespace itk
{

/** \class ImageRandomIteratorWithIndex
 * \brief Multi-dimensional image iterator which only walks a region.
 * 
 * ImageRandomIteratorWithIndex is a templated class to represent a multi-dimensional
 * iterator. ImageRandomIteratorWithIndex is templated over the image type
 * ImageRandomIteratorWithIndex is constrained to walk only within the 
 * specified region. It samples random pixel positions at each increment.
 *
 * ImageRandomIteratorWithIndex is a multi-dimensional iterator, requiring more
 * information be specified before the iterator can be used than conventional
 * iterators. Whereas the std::vector::iterator from the STL only needs to be
 * passed a pointer to establish the iterator, the multi-dimensional image
 * iterator needs a pointer, the size of the buffer, the size of the region,
 * the start index of the buffer, and the start index of the region. To gain
 * access to this information, ImageRandomIteratorWithIndex holds a reference to the
 * image over which it is traversing.
 *
 * ImageRandomIteratorWithIndex assumes a particular layout of the image data. The
 * is arranged in a 1D array as if it were [][][][slice][row][col] with
 * Index[0] = col, Index[1] = row, Index[2] = slice, etc.
 *
 * operator++ provides a simple syntax for walking around a region of
 * a multidimensional image. operator++ iterates performs a jump to a random
 * position on the Image Buffer. This is designed to facilitate the extraction
 * of random samples from the image.
 *
 * This is the typical use of this iterator in a loop:
 *
 * \code
 *  
 * ImageRandomIteratorWithIndex<ImageType> it( image, image->GetRequestedRegion() );
 * 
 * it.SetNumberOfSamples(2);
 * it.GoToBegin();
 * while( !it.IsAtEnd() )
 * {
 *   it.Get();
 *   ++it;  // here it jumps to another random position inside the region
 *  } 
 *
 *  \endcode
 *
 * \example  Common/itkImageRandomIteratorWithIndexTest.cxx
 *
 *
 * \ingroup ImageIterators
 *
 *
 */
template<typename TImage>
class ImageRandomIteratorWithIndex : public ImageIteratorWithIndex<TImage>
{
public:
  /** Standard class typedefs. */
  typedef ImageRandomIteratorWithIndex Self;
  typedef ImageIteratorWithIndex<TImage>  Superclass;
  
  /** Index typedef support. While this was already typdef'ed in the superclass
   * it needs to be redone here for this subclass to compile properly with gcc.
   * Note that we have to rescope Index back to itk::Index to that is it not
   * confused with ImageIterator::Index. */
  typedef typename TImage::IndexType   IndexType;

  /** Region typedef support. While this was already typdef'ed in the superclass
   * it needs to be redone here for this subclass to compile properly with gcc.
   * Note that we have to rescope Region back to itk::ImageRegion so that is
   * it not confused with ImageIterator::Index. */
  typedef typename TImage::RegionType RegionType;
  
  /** Image typedef support. While this was already typdef'ed in the superclass
   * it needs to be redone here for this subclass to compile properly with gcc.
   * Note that we have to rescope Index back to itk::Index to that is it not
   * confused with ImageIterator::Index. */
  typedef TImage ImageType;

  /** PixelContainer typedef support. Used to refer to the container for
   * the pixel data. While this was already typdef'ed in the superclass
   * it needs to be redone here for this subclass to compile properly with gcc. */
  typedef typename TImage::PixelContainer PixelContainer;
  typedef typename PixelContainer::Pointer PixelContainerPointer;
  
  /** Default constructor. Needed since we provide a cast constructor. */
  ImageRandomIteratorWithIndex();
  virtual ~ImageRandomIteratorWithIndex() {};
  
  /** Constructor establishes an iterator to walk a particular image and a
   * particular region of that image. */
  ImageRandomIteratorWithIndex(ImageType *ptr, const RegionType& region);

  /** Constructor that can be used to cast from an ImageIterator to an
   * ImageRandomIteratorWithIndex. Many routines return an ImageIterator but for a
   * particular task, you may want an ImageRandomIteratorWithIndex.  Rather than
   * provide overloaded APIs that return different types of Iterators, itk
   * returns ImageIterators and uses constructors to cast from an
   * ImageIterator to a ImageRandomIteratorWithIndex. */
  ImageRandomIteratorWithIndex( const ImageIteratorWithIndex<TImage> &it)
    { this->ImageIteratorWithIndex<TImage>::operator=(it); }

  /** Move an iterator to the beginning of the region. */
  virtual void GoToBegin(void);

  /** Move an iterator to the End of the region. */
  virtual void GoToEnd(void);

  /** Is the iterator at the beginning of the region? */
  bool IsAtBegin(void) const
    { return (m_NumberOfSamplesDone==0) ; }

  /** Is the iterator at the end of the region? */
  bool IsAtEnd(void) const
    { return (m_NumberOfSamplesDone > m_NumberOfSamplesRequested);  }
 
  /** Increment (prefix) the selected dimension.
   * No bounds checking is performed. \sa GetIndex \sa operator-- */
  Self & operator++();

  /** Decrement (prefix) the selected dimension.
   * No bounds checking is performed. \sa GetIndex \sa operator++ */
  Self & operator--();
  
  /** Set/Get number of random samples to get from the image region */
  void SetNumberOfSamples( unsigned long number );
  unsigned long GetNumberOfSamples( void ) const;

private:
    unsigned long  m_NumberOfSamplesRequested;
    unsigned long  m_NumberOfSamplesDone;
    unsigned long  m_NumberOfPixelsInRegion;
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkImageRandomIteratorWithIndex.txx"
#endif

#endif 



