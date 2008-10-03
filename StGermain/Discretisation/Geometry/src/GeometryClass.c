/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**
** Copyright (C), 2003, Victorian Partnership for Advanced Computing (VPAC) Ltd, 110 Victoria Street, Melbourne, 3053, Australia.
**
** Authors:
**	Stevan M. Quenette, Senior Software Engineer, VPAC. (steve@vpac.org)
**	Patrick D. Sunter, Software Engineer, VPAC. (pds@vpac.org)
**	Luke J. Hodkinson, Computational Engineer, VPAC. (lhodkins@vpac.org)
**	Siew-Ching Tan, Software Engineer, VPAC. (siew@vpac.org) ) {
	IrregTopology* self = (IrregTopology*)ir
**	Alan H. Lo, Computational Engineer, VPAC. (alan@vpac.org)
**	Raquibul Hassan, Computational Engineer, VPAC. (raq@vpac.org)
**
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the GNU Lesser General Public
**  License as published by the Free Software Foundation; either
**  version 2.1 of the License, or (at your option) any later version.
**
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**  Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public
**  License along with this library; if not, write to the Free Software
**  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
**
** $Id: GeometryClass.c 3462 2006-02-19 06:53:24Z WalterLandry $
**
**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <mpi.h>
#include "Base/Base.h"


#include "units.h"
#include "types.h"
#include "GeometryClass.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/* Textual name of this class */
const Type Geometry_Type = "Geometry";

/*----------------------------------------------------------------------------------------------------------------------------------
** Constructors
*/

Geometry* _Geometry_New(
		SizeT						_sizeOfSelf, 
		Type						type,
		Stg_Class_DeleteFunction*				_delete,
		Stg_Class_PrintFunction*				_print,
		Stg_Class_CopyFunction*				_copy, 
		Stg_Component_DefaultConstructorFunction*	_defaultConstructor,
		Stg_Component_ConstructFunction*			_construct,
		Stg_Component_BuildFunction*		_build,
		Stg_Component_InitialiseFunction*		_initialise,
		Stg_Component_ExecuteFunction*		_execute,
		Stg_Component_DestroyFunction*		_destroy,
		Name							name,
		Bool							initFlag,
		Geometry_BuildPointsFunction*			buildPoints,
		Geometry_PointAtFunction*			pointAt,
		Dictionary*					dictionary )
{
	Geometry* self;
	
	/* Allocate memory */
	assert( _sizeOfSelf >= sizeof(Geometry) );
	self = (Geometry*)_Stg_Component_New( _sizeOfSelf, type, _delete, _print, _copy, _defaultConstructor, _construct, _build, 
			_initialise, _execute, _destroy, name, NON_GLOBAL );
	
	/* General info */
	self->dictionary = dictionary;
	
	/* Virtual info */
	self->buildPoints = buildPoints;
	self->pointAt = pointAt;
	
	/* Geometry info */
	if( initFlag ){
		_Geometry_Init( self );
	}
	
	return self;
}

void _Geometry_Init(
		Geometry*					self )
{
	/* General and Virtual info should already be set */
	
	/* Geometry info */
	self->isConstructed = True;
}


/*----------------------------------------------------------------------------------------------------------------------------------
** Virtual functions
*/

void _Geometry_Delete( void* geometry ) {
	Geometry* self = (Geometry*)geometry;
	
	/* Stg_Class_Delete parent */
	_Stg_Class_Delete( self );
}


void _Geometry_Print( void* geometry, Stream* stream ) {
	Geometry* self = (Geometry*)geometry;
	
	/* Set the Journal for printing informations */
	Stream* geometryStream;
	geometryStream = Journal_Register( InfoStream_Type, "GeometryStream" );

	/* Print parent */
	_Stg_Class_Print( self, stream );
	
	/* General info */
	Journal_Printf( stream, "Geometry (ptr): (%p)\n", self );
	
	/* Virtual info */
	
	/* Geometry info */
}


void* _Geometry_Copy( void* geometry, void* dest, Bool deep, Name nameExt, PtrMap* ptrMap ) {
	Geometry*	self = (Geometry*)geometry;
	Geometry*	newGeometry;
	
	newGeometry = (Geometry*)_Stg_Class_Copy( self, dest, deep, nameExt, ptrMap );
	
	/* Virtual methods */
	newGeometry->buildPoints = self->buildPoints;
	newGeometry->pointAt = self->pointAt;
	
	newGeometry->pointCount = self->pointCount;
	
	return (void*)newGeometry;
}


/*--------------------------------------------------------------------------------------------------------------------------
** Public Functions
*/


/*----------------------------------------------------------------------------------------------------------------------------------
** Private Functions
*/

