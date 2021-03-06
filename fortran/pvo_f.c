
/// vim: tabstop=4:expandtab:hlsearch

/* Copyright 2010 University of Lugano. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice, this list of
 *       conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright notice, this list
 *       of conditions and the following disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those of the
 * authors and should not be interpreted as representing official policies, either expressed
 * or implied, of the University of Lugano.
 */

#include "pvo.h"
#include "pvo_report.h"
#include "pvo_memory.h"


/* --------------------------------------------------------------------------------
   Functions in pvo_mpi.h
   -------------------------------------------------------------------------------- */
int PVO_FNAME(pvo_world_size,PVO_WORLD_SIZE)() {
    return pvo_world_size();
}

int PVO_FNAME(pvo_world_rank,PVO_WORLD_RANK)() {
    return pvo_world_rank();
}

/* --------------------------------------------------------------------------------
   Functions in pvo_decls.h
   -------------------------------------------------------------------------------- */
void PVO_FNAME(pvo_init,PVO_INIT)( MPI_Fint* fcomm, int* ierr ) {
    MPI_Comm comm = MPI_Comm_f2c(*fcomm);
    *ierr = pvo_init( comm );
}

void PVO_FNAME(pvo_quit,PVO_QUIT)( int* ierr ) {
    *ierr = pvo_quit();
}

void PVO_FNAME(pvo_physical_node_uid,PVO_PHYSICAL_NODE_UID)( int* uid ) {
    *uid = pvo_physical_node_uid();
}

/* --------------------------------------------------------------------------------
   Functions in pvo_var.h
   -------------------------------------------------------------------------------- */

/// The function pvo_var_create and pvo_var_delete are not exposed to the Fortran
/// programmer. They are intended only for internal use

/* --------------------------------------------------------------------------------
   Functions in pvo_cookie.h
   -------------------------------------------------------------------------------- */
void PVO_FNAME(pvo_cookie_create,PVO_COOKIE_CREATE)( int* color, void* cookie, int* ierr ) {
    *ierr = pvo_cookie_create( *color, cookie );
}

void PVO_FNAME(pvo_cookie_delete,PVO_COOKIE_DELETE)( void* cookie, int* ierr ) {
    *ierr = pvo_cookie_delete( *(pvo_cookie_t* )cookie );
}

void PVO_FNAME(pvo_cookie_insert_var_int32,PVO_COOKIE_INSERT_VAR_INT32)( void*       cookie,
                                                                         int*        grp,
                                                                         int*        ncomps,
                                                                         const char* name,
                                                                         const void* ptr,
                                                                         int*        ierr ) {
    *ierr = pvo_cookie_insert_var( *(pvo_cookie_t* )cookie, *grp,
                                   PVO_VAR_INT32, *ncomps, name, ptr );
}

void PVO_FNAME(pvo_cookie_insert_var_int64,PVO_COOKIE_INSERT_VAR_INT64)( void*       cookie,
                                                                         int*        grp,
                                                                         int*        ncomps,
                                                                         const char* name,
                                                                         const void* ptr,
                                                                         int*        ierr ) {
    *ierr = pvo_cookie_insert_var( *(pvo_cookie_t* )cookie, *grp,
                                   PVO_VAR_INT64, *ncomps, name, ptr );
}

void PVO_FNAME(pvo_cookie_insert_var_float32,PVO_COOKIE_INSERT_VAR_FLOAT32)( void*       cookie,
                                                                             int*        grp,
                                                                             int*        ncomps,
                                                                             const char* name,
                                                                             const void* ptr,
                                                                             int*        ierr ) {
    *ierr = pvo_cookie_insert_var( *(pvo_cookie_t* )cookie, *grp,
                                   PVO_VAR_FLOAT32, *ncomps, name, ptr );
}

void PVO_FNAME(pvo_cookie_insert_var_float64,PVO_COOKIE_INSERT_VAR_FLOAT64)( void*       cookie,
                                                                             int*        grp,
                                                                             int*        ncomps,
                                                                             const char* name,
                                                                             const void* ptr,
                                                                             int*        ierr ) {
    *ierr = pvo_cookie_insert_var( *(pvo_cookie_t* )cookie, *grp,
                                   PVO_VAR_FLOAT64, *ncomps, name, ptr );
}

void PVO_FNAME(pvo_cookie_remove_var,PVO_COOKIE_REMOVE_VAR)( void*       cookie,
                                                             const char* name,
                                                             int*        ierr ) {
    *ierr = pvo_cookie_remove_var( *(pvo_cookie_t* )cookie, name );
}

void PVO_FNAME(pvo_cookie_number_var,PVO_COOKIE_NUMBER_VAR)( void* cookie, int* num, int* ierr ) {
    *num  = pvo_cookie_number_var( *(pvo_cookie_t* )cookie );
    *ierr = 0;  /// Keep this for consistency of the Fortran interface
}

/* --------------------------------------------------------------------------------
   Functions in pvo_file.h
   -------------------------------------------------------------------------------- */
void PVO_FNAME(pvo_file_create,PVO_FILE_CREATE)( const char* filename,
                                                 int*        bo,
                                                 void*       cookie,
                                                 long*       fh,
                                                 int*        ierr ) {
    *fh   = (long )pvo_malloc( 100*sizeof(struct pvo_file) );
    *ierr = pvo_file_create( filename, *bo, *(pvo_cookie_t* )cookie, (pvo_file_t )*fh );
}

void PVO_FNAME(pvo_file_write,PVO_FILE_WRITE)( void* fh, int* ierr ) {
    *ierr = pvo_file_write( *(pvo_file_t* )fh );
}

void PVO_FNAME(pvo_file_delete,PVO_FILE_DELETE)( void* fh, int* ierr ) {
    *ierr = pvo_file_delete( (pvo_file_t )fh );
    pvo_free( *(void** )fh );
}

/* --------------------------------------------------------------------------------
   Functions in pvo_vtu_file.h
   -------------------------------------------------------------------------------- */
void PVO_FNAME(pvo_vtu_file_open,PVO_VTU_FILE_OPEN)( const char*   filename,
                                                     void*         cookie,
                                                     long*         nnodes,
                                                     pvo_float3_t* pts,
                                                     long*         ncells,
                                                     int*          cia,
                                                     int*          cja,
                                                     int*          types,
                                                     void*         fh,
                                                     int*          ierr ) {
    size_t   i;
    uint8_t* ui8types;

    /// Since we don't have a uint8_t equivalent type in Fortran we
    /// need to copy the values over to a new array
    ui8types = pvo_malloc( (*ncells)*sizeof(uint8_t) );
    for(i = 0; i < (size_t )*ncells; ++i) {
        ui8types[i] = types[i];
    }

    *ierr = pvo_vtu_file_open( filename, *(pvo_cookie_t* )cookie, *nnodes, pts,
                               *ncells, cia, cja, ui8types, fh );
}

void PVO_FNAME(pvo_vtu_file_close,PVO_VTU_FILE_CLOSE)( void* fh, int* ierr ) {
    uint8_t* ui8types;

    ui8types = (*(pvo_vtu_file_t* )fh)->types;  /// Allocated in pvo_vtu_file_open
    *ierr = pvo_vtu_file_close( *(pvo_vtu_file_t* )fh );
    pvo_free( ui8types );
}

/* --------------------------------------------------------------------------------
   Functions in pvo_vtp_file.h
   -------------------------------------------------------------------------------- */
void PVO_FNAME(pvo_vtp_file_open,PVO_VTP_FILE_OPEN)( const char*   filename,
                                                     void*         cookie,
                                                     long*         npoints,
                                                     pvo_float3_t* pts,
                                                     void*         fh,
                                                     int*          ierr ) {
    *ierr = pvo_vtp_file_open( filename, *(pvo_cookie_t* )cookie, *npoints, pts, fh );
}

void PVO_FNAME(pvo_vtp_file_close,PVO_VTP_FILE_CLOSE)( void* fh, int* ierr ) {
    *ierr = pvo_vtp_file_close( *(pvo_vtp_file_t* )fh );
}

/* --------------------------------------------------------------------------------
   Functions in pvo_vti_file.h
   -------------------------------------------------------------------------------- */
void PVO_FNAME(pvo_vti_file_open,PVO_VTI_FILE_OPEN)( const char*    filename,
                                                     void*          cookie,
                                                     const int*     whole_extent,
                                                     int*           ghost_level,
                                                     const float*   origin,
                                                     const float*   spacing,
                                                     const int*     local_extent,
                                                     void*          fh,
                                                     int*           ierr ) {
    *ierr = pvo_vti_file_open( filename, *(pvo_cookie_t* )cookie, whole_extent,
                               *ghost_level, origin, spacing, local_extent, fh );
}

void PVO_FNAME(pvo_vti_file_close,PVO_VTI_FILE_CLOSE)( void* fh, int* ierr ) {
    *ierr = pvo_vti_file_close( *(pvo_vti_file_t* )fh );
}

/* --------------------------------------------------------------------------------
   Functions in pvo_vts_file.h
   -------------------------------------------------------------------------------- */
void PVO_FNAME(pvo_vts_file_open,PVO_VTI_FILE_OPEN)( const char*    filename,
                                                     void*          cookie,
                                                     const int*     whole_extent,
                                                     int*           ghost_level,
                                                     const int*     local_extent,
                                                     pvo_float3_t*  pts,
                                                     void*          fh,
                                                     int*           ierr ) {
    *ierr = pvo_vts_file_open( filename, *(pvo_cookie_t* )cookie, whole_extent,
                               *ghost_level, local_extent, pts, fh );
}

void PVO_FNAME(pvo_vts_file_close,PVO_VTI_FILE_CLOSE)( void* fh, int* ierr ) {
    *ierr = pvo_vts_file_close( *(pvo_vts_file_t* )fh );
}

/* --------------------------------------------------------------------------------
   MPI stubs
   -------------------------------------------------------------------------------- */
#if 0 == PVO_HAVE_MPI
#define PVO_F_MPI_IN_PLACE  PVO_FNAME(pvo_mpi_f_in_place,PVO_MPI_F_IN_PLACE)
int PVO_F_MPI_IN_PLACE;

void PVO_FNAME(mpi_init,MPI_INIT)( int* ierr )
{
    *ierr = 0;
}

void PVO_FNAME(mpi_allreduce,MPI_ALLREDUCE)( void*         sendbuf,
                                             void*         recvbuf,
                                             int*          count,
                                             MPI_Datatype* datatype,
                                             MPI_Op*       op,
                                             MPI_Comm*     comm,
                                             int*          ierr ) {
    if(&PVO_F_MPI_IN_PLACE == sendbuf) {
        *ierr = MPI_Allreduce( MPI_IN_PLACE, recvbuf, *count, *datatype, *op, *comm );
    } else {
        *ierr = MPI_Allreduce( sendbuf, recvbuf, *count, *datatype, *op, *comm );
    }
}

double PVO_FNAME(mpi_wtime,MPI_WTIME)() {
    return MPI_Wtime();
}

#endif

