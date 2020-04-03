import React from 'react';
import Button from '@material-ui/core/Button';
import Card from '@material-ui/core/Card';
import CardActions from '@material-ui/core/CardActions';
import CardContent from '@material-ui/core/CardContent';
import Typography from '@material-ui/core/Typography';
import UrlsContext from 'contexts/UrlsContext';
import { makeStyles } from '@material-ui/core/styles';

const useStyles = makeStyles({
  root: {
    minWidth: '300px'
  }
});

function PeerCard(props) {
  const classes = useStyles();
  const urls = React.useContext(UrlsContext);
  const [peer, setPeer] = React.useState({});

  React.useEffect(() => {
    // fetch(`http://${urls.nodeUrl}/blocks/${props.blockHeight}`)
    //   .then(result => result.json())
    //   .then(block => {
    //     setBlock(block);
    //   });
    setPeer({ hostname: props.hostname });
  }, [urls.nodeUrl, props.hostname]);

  function renderCardActions() {
    if (props.hideAction) return '';

    return (
      <CardActions>
        <Button size="small" href={`/#/network/${props.hostname}/`}>
          View Peer
        </Button>
      </CardActions>
    );
  }

  return (
    <Card className={classes.root}>
      <CardContent>
        <Typography variant="h5" component="h2">
          {peer.hostname}
        </Typography>
      </CardContent>

      {renderCardActions()}
    </Card>
  );
}

export default PeerCard;
