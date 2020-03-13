%% Insert data here
data = [];

%% Fitting the Data
X = data(:, 1);
y = data(:, 2);
estimate = fit(X, y, 'poly1') % Requires curve fitting toolbox
scatter(X, y);
hold on
plot(estimate)
