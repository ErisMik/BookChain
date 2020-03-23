import React from 'react';
import PeerCard from 'components/PeerCard';
import ChevronRightIcon from '@material-ui/icons/ChevronRight';
import Divider from '@material-ui/core/Divider';
import Drawer from '@material-ui/core/Drawer';
import IconButton from '@material-ui/core/IconButton';
import Paper from '@material-ui/core/Paper';
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableContainer from '@material-ui/core/TableContainer';
import TableHead from '@material-ui/core/TableHead';
import TablePagination from '@material-ui/core/TablePagination';
import TableRow from '@material-ui/core/TableRow';
import UrlsContext from 'contexts/UrlsContext';
import { makeStyles } from '@material-ui/core/styles';

const columns = [
  { id: 'hostname', label: 'Hostname', minWidth: 100 },
  { id: 'queueLength', label: 'Job Queue Size', minWidth: 100 }
];

const useStyles = makeStyles({
  root: {
    width: '100%'
  },
  container: {
    maxHeight: '85vh'
  },
  tableDataCell: {
    maxWidth: '80vh',
    whiteSpace: 'nowrap',
    overflow: 'hidden',
    textOverflow: 'ellipsis'
  }
});

function NetworkView(props) {
  const classes = useStyles();
  const urls = React.useContext(UrlsContext);
  const [peers, setPeers] = React.useState([]);
  const [selectedPeer, setSelectedPeer] = React.useState({});

  const [page, setPage] = React.useState(0);
  const [rowsPerPage, setRowsPerPage] = React.useState(25);
  const [drawerOpen, setDrawerOpen] = React.useState(false);

  React.useEffect(() => {
    fetch(`http://${urls.nodeUrl}/peers?page=${page}&page_size=${rowsPerPage}`)
      .then(result => result.json())
      .then(peersResult => {
        setPeers([]);

        peersResult.forEach(peer => {
          fetch(`http://${peer.hostname}/jobs/queuelength`)
            .then(result => result.json())
            .then(result => {
              setPeers(peers => [...peers, { ...peer, ...result }]);
            })
            .catch(() => {
              setPeers(peers => [...peers, peer]);
            });
        });
      });
  }, [urls.nodeUrl, page, rowsPerPage]);

  const handleChangePage = (event, newPage) => {
    setPage(newPage);
  };

  const handleChangeRowsPerPage = event => {
    setRowsPerPage(+event.target.value);
    setPage(0);
  };

  const handleDrawerOpen = peer => {
    setSelectedPeer(peer);
    setDrawerOpen(true);
  };

  const handleDrawerClose = () => {
    setDrawerOpen(false);
  };

  function renderRows() {
    return peers.map(peer => {
      return (
        <TableRow hover role="checkbox" tabIndex={-1} key={peer.hostname}>
          {columns.map(column => {
            const value = peer[column.id];
            return (
              <TableCell
                key={column.id}
                align={column.align}
                className={classes.tableDataCell}
                onClick={() => handleDrawerOpen(peer)}
              >
                {value}
              </TableCell>
            );
          })}
        </TableRow>
      );
    });
  }

  return (
    <Paper className={classes.root}>
      <PeerCard hostname={urls.nodeUrl} />
      <Paper>
        <TableContainer className={classes.container}>
          <Table stickyHeader size="small" aria-label="blocks-table">
            <TableHead>
              <TableRow>
                {columns.map(column => (
                  <TableCell
                    key={column.id}
                    align={column.align}
                    style={{ minWidth: column.minWidth }}
                  >
                    {column.label}
                  </TableCell>
                ))}
              </TableRow>
            </TableHead>
            <TableBody>{renderRows()}</TableBody>
          </Table>
        </TableContainer>
        <TablePagination
          rowsPerPageOptions={[10, 25, 100, 500]}
          component="div"
          count={0}
          rowsPerPage={rowsPerPage}
          page={page}
          onChangePage={handleChangePage}
          onChangeRowsPerPage={handleChangeRowsPerPage}
        />
      </Paper>
      <Drawer
        className={classes.drawer}
        variant="persistent"
        anchor="right"
        open={drawerOpen}
        classes={{
          paper: classes.drawerPaper
        }}
      >
        <div className={classes.drawerHeader}>
          <IconButton onClick={handleDrawerClose}>
            <ChevronRightIcon />
          </IconButton>
        </div>
        <Divider />
        <PeerCard hostname={selectedPeer.hostname} />
      </Drawer>
    </Paper>
  );
}

export default NetworkView;
