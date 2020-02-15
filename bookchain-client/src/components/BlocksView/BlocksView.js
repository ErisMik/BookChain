import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Paper from '@material-ui/core/Paper';
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableContainer from '@material-ui/core/TableContainer';
import TableHead from '@material-ui/core/TableHead';
import TableRow from '@material-ui/core/TableRow';

const columns = [
  { id: 'blockHeight', label: 'Height', minWidth: 170 },
  { id: 'blockHash', label: 'Hash', minWidth: 170 },
  { id: 'data', label: 'Data', minWidth: 170 }
];

const useStyles = makeStyles({
  root: {
    width: '100%'
  },
  container: {
    maxHeight: '90vh'
  }
});

function BlocksView(props) {
  const classes = useStyles();

  const [blocks, setBlocks] = React.useState([]);
  React.useEffect(() => {
    fetch('http://localhost:8000/blocks')
      .then(result => result.json())
      .then(blocks => setBlocks(blocks));
  }, []);

  function renderRows() {
    return blocks.map(block => {
      return (
        <TableRow hover role="checkbox" tabIndex={-1} key={block.height}>
          {columns.map(column => {
            const value = block[column.id];
            return (
              <TableCell key={column.id} align={column.align}>
                {column.format && typeof value === 'number'
                  ? column.format(value)
                  : value}
              </TableCell>
            );
          })}
        </TableRow>
      );
    });
  }

  return (
    <Paper className={classes.root}>
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
    </Paper>
  );
}

export default BlocksView;
