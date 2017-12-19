#include "pointtransformnode.h"

#include <QMatrix4x4>

#include <fugio/core/uuid.h>

#include <fugio/context_interface.h>

#include <fugio/pin_variant_iterator.h>

PointTransformNode::PointTransformNode( QSharedPointer<fugio::NodeInterface> pNode )
	: NodeControlBase( pNode )
{
	FUGID( PIN_INPUT_MATRIX, "B7AE4E04-0473-4929-955C-2703F99275A6" );
	FUGID( PIN_INPUT_POINTS, "6B82A907-28AF-46C0-9551-58144374BC94" );
	FUGID( PIN_OUTPUT_POINTS, "683EB58D-715C-466A-957C-6C5BF0057895" );

	mPinInputMatrix = pinInput( "Matrix", PIN_INPUT_MATRIX );

	mPinInputPoints = pinInput( "Points", PIN_INPUT_POINTS );

	mValOutputPoints = pinOutput<fugio::ArrayInterface *>( "Points", mPinOutputPoints, PID_ARRAY, PIN_OUTPUT_POINTS );

	mValOutputPoints->setType( QMetaType::QPointF );
	mValOutputPoints->setSize( 1 );
	mValOutputPoints->setStride( sizeof( QPointF ) );
}

void PointTransformNode::inputsUpdated( qint64 pTimeStamp )
{
	NodeControlBase::inputsUpdated( pTimeStamp );

	QMatrix4x4					Matrix = variant( mPinInputMatrix ).value<QMatrix4x4>();

	fugio::PinVariantIterator	Points( mPinInputPoints );

	const int					PointCount = Points.size();

	mValOutputPoints->setCount( PointCount );

	if( PointCount )
	{
		QPointF		*o = (QPointF *)mValOutputPoints->array();

		for( int i = 0 ; i < PointCount ; i++ )
		{
			QPointF		p = Points.index( i ).toPointF();

			o[ i ] = Matrix * p;
		}
	}

	pinUpdated( mPinOutputPoints );
}