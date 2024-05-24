import pandas as pd
import plotly.graph_objects as go
from dash import Dash, dcc, html
from dash.dependencies import Input, Output, State
import copy

# Read the CSV file
df = pd.read_csv('out/bird_flight.csv')

# Define a list of colors for different iterations
colors = ['blue', 'green', 'red', 'cyan', 'magenta', 'yellow', 'black']
color_map = {iteration: colors[i % len(colors)] for i, iteration in enumerate(df['iteration'].unique())}

# Create the figure
fig = go.Figure()
bird_shape_map = {}  # Map to store bird ID to shape indices

# Plot each iteration
shape_idx = 0
for iteration in df['iteration'].unique():
    iter_data = df[df['iteration'] == iteration]
    color = color_map[iteration]

    # Plot circles and vectors
    for _, row in iter_data.iterrows():
        bird_id = row['id']
        
        # Add circle annotation
        fig.add_shape(
            type="circle",
            xref="x", yref="y",
            x0=row['x'] - row['radius'], y0=row['y'] - row['radius'],
            x1=row['x'] + row['radius'], y1=row['y'] + row['radius'],
            line=dict(color=color, width=2),
            opacity=0.2  # Lower shape opacity
        )
        if bird_id not in bird_shape_map:
            bird_shape_map[bird_id] = []
        bird_shape_map[bird_id].append(shape_idx)
        shape_idx += 1

        # Add the starting point (marker for hover)
        fig.add_trace(go.Scatter(
            x=[row['x']],
            y=[row['y']],
            mode='markers',
            marker=dict(size=row['radius']*10, color=color, opacity=0.7),
            hoverinfo='text',
            name=f'Bird ID {bird_id} (Iter {iteration})',
            text=f'Bird ID: {bird_id}, Iteration: {iteration}',
            customdata=[bird_id]
        ))

        # Add the line (flight path)
        fig.add_trace(go.Scatter(
            x=[row['x'], row['x'] + row['dx']],
            y=[row['y'], row['y'] + row['dy']],
            mode='lines',
            line=dict(color=color, width=4),
            showlegend=False,
            hoverinfo='text',
            text=f'Bird ID: {bird_id}, Iteration: {iteration}',
            customdata=[bird_id]
        ))

# Update the layout
fig.update_layout(
    title='Bird Positions and Movements Across Iterations',
    xaxis_title='X Position',
    yaxis_title='Y Position',
    legend_title='Birds',
    showlegend=True,
    hovermode='closest',
    xaxis=dict(scaleanchor="y", scaleratio=1),
    yaxis=dict(scaleanchor="x", scaleratio=1)
)

# Create the Dash application
app = Dash(__name__)

app.layout = html.Div([
    dcc.Graph(id='bird-flight-graph', figure=fig, style={'width': '100vw', 'height': '100vh'}),
    dcc.Store(id='axis-ranges', data={'xaxis': [None, None], 'yaxis': [None, None]})
])

@app.callback(
    Output('axis-ranges', 'data'),
    [Input('bird-flight-graph', 'relayoutData')]
)
def store_axis_ranges(relayoutData):
    current_ranges = {'xaxis': [None, None], 'yaxis': [None, None]}
    
    if relayoutData:
        if 'xaxis.range[0]' in relayoutData and 'xaxis.range[1]' in relayoutData:
            current_ranges['xaxis'] = [relayoutData['xaxis.range[0]'], relayoutData['xaxis.range[1]']]
        if 'yaxis.range[0]' in relayoutData and 'yaxis.range[1]' in relayoutData:
            current_ranges['yaxis'] = [relayoutData['yaxis.range[0]'], relayoutData['yaxis.range[1]']]
    
    return current_ranges

@app.callback(
    Output('bird-flight-graph', 'figure'),
    [Input('bird-flight-graph', 'hoverData')],
    [State('axis-ranges', 'data')]
)
def update_hover(hoverData, axis_ranges):
    # Create a deep copy of the figure
    new_fig = copy.deepcopy(fig)

    # Reset the opacity for all traces and shapes
    for trace in new_fig['data']:
        trace['opacity'] = 0.2

    for shape in new_fig['layout']['shapes']:
        shape['opacity'] = 0.2

    # Highlight traces and shapes related to the hovered bird ID
    if hoverData and 'customdata' in hoverData['points'][0]:
        bird_id = hoverData['points'][0]['customdata']
        for trace in new_fig['data']:
            if trace['customdata'] and bird_id in trace['customdata']:
                trace['opacity'] = 1
        
        if bird_id in bird_shape_map:
            for shape_idx in bird_shape_map[bird_id]:
                new_fig['layout']['shapes'][shape_idx]['opacity'] = 1

    # Restore the zoom level
    if axis_ranges['xaxis'] != [None, None] and axis_ranges['yaxis'] != [None, None]:
        new_fig.update_layout(
            xaxis=dict(range=axis_ranges['xaxis']),
            yaxis=dict(range=axis_ranges['yaxis'])
        )

    return new_fig

if __name__ == '__main__':
    app.run_server(debug=True)
