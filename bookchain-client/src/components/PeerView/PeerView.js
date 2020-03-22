import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import { useParams } from 'react-router-dom';
import PeerCard from 'components/PeerCard';
import Paper from '@material-ui/core/Paper';

const useStyles = makeStyles({
  root: {
    width: '100%'
  }
});

function PeerView(props) {
  const classes = useStyles();
  const { identifier } = useParams();

  return (
    <Paper className={classes.root}>
      <PeerCard hideAction={true} ipAddress={identifier} />
    </Paper>
  );
}

export default PeerView;
