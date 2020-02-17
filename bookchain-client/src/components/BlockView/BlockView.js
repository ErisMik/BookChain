import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import { useParams } from 'react-router-dom';
import BlockCard from 'components/BlockCard';
import Paper from '@material-ui/core/Paper';

const useStyles = makeStyles({
  root: {
    width: '100%'
  }
});

function BlockView(props) {
  const classes = useStyles();
  const { height } = useParams();

  return (
    <Paper className={classes.root}>
      <BlockCard blockHeight={height} />
    </Paper>
  );
}

export default BlockView;
