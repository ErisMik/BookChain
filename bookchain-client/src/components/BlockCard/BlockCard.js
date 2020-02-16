import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Button from '@material-ui/core/Button';
import Card from '@material-ui/core/Card';
import CardActions from '@material-ui/core/CardActions';
import CardContent from '@material-ui/core/CardContent';
import Typography from '@material-ui/core/Typography';
import UrlsContext from 'contexts/UrlsContext';

const useStyles = makeStyles({
  root: {
    minWidth: '300px'
  }
});

function BlockCard(props) {
  const classes = useStyles();
  const urls = React.useContext(UrlsContext);
  const [block, setBlock] = React.useState({});

  React.useEffect(() => {
    fetch(`http://${urls.nodeUrl}/blocks/${props.blockHeight}`)
      .then(result => result.json())
      .then(block => {
        setBlock(block);
      });
  }, [urls.nodeUrl, props.blockHeight]);

  function renderCardActions() {
    if (props.hideAction) return '';

    return (
      <CardActions>
        <Button size="small">View Data</Button>
      </CardActions>
    );
  }

  return (
    <Card className={classes.root}>
      <CardContent>
        <Typography variant="h5" component="h2">
          {block.blockHash}
        </Typography>
        <Typography variant="body2" component="p">
          {block.blockHeight}
        </Typography>
        <Typography variant="body2" component="p">
          {block.prevHash}
        </Typography>
        <Typography variant="body2" component="p">
          {block.nonce}
        </Typography>
        <Typography variant="body2" component="p">
          {block.signature}
        </Typography>
      </CardContent>

      {renderCardActions()}
    </Card>
  );
}

export default BlockCard;
