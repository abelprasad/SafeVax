// API base URL
const API_URL = 'http://localhost:8080/api';

// Fetch and update system status
async function fetchStatus() {
    try {
        const response = await fetch(`${API_URL}/status`);
        const data = await response.json();

        document.getElementById('totalVaccines').textContent = data.totalVaccines.toLocaleString();
        document.getElementById('availableVaccines').textContent = data.availableVaccines.toLocaleString();
        document.getElementById('avgWaitTime').textContent = data.averageWaitTime.toFixed(2);
        document.getElementById('throughput').textContent = data.throughput.toFixed(2);

        // Show starvation alert if detected
        const alertDiv = document.getElementById('starvationAlert');
        if (data.hasStarvation) {
            alertDiv.style.display = 'block';
        } else {
            alertDiv.style.display = 'none';
        }
    } catch (error) {
        console.error('Error fetching status:', error);
        showNotification('Error connecting to server', 'error');
    }
}

// Fetch and display hospitals
async function fetchHospitals() {
    try {
        const response = await fetch(`${API_URL}/hospitals`);
        const data = await response.json();

        const tbody = document.getElementById('hospitalsTableBody');
        tbody.innerHTML = '';

        data.hospitals.forEach(hospital => {
            const row = document.createElement('tr');

            const statusBadge = hospital.isStarved
                ? '<span class="status-badge status-starved">STARVED</span>'
                : '<span class="status-badge status-normal">NORMAL</span>';

            row.innerHTML = `
                <td>${hospital.id}</td>
                <td>${hospital.name}</td>
                <td>${hospital.priority}</td>
                <td>${hospital.currentVaccines.toLocaleString()}</td>
                <td>${hospital.requestedVaccines.toLocaleString()}</td>
                <td>${hospital.highRiskPopulation.toLocaleString()}</td>
                <td>${hospital.waitTime.toFixed(1)}</td>
                <td>${statusBadge}</td>
                <td>
                    <button class="btn btn-primary btn-small" onclick="quickRequest(${hospital.id})">
                        Request
                    </button>
                </td>
            `;
            tbody.appendChild(row);
        });
    } catch (error) {
        console.error('Error fetching hospitals:', error);
        showNotification('Error fetching hospitals', 'error');
    }
}

// Submit a vaccine request
async function submitRequest() {
    const hospitalId = parseInt(document.getElementById('requestHospitalId').value);
    const amount = parseInt(document.getElementById('requestAmount').value);

    if (!hospitalId || !amount || amount <= 0) {
        showNotification('Please enter valid hospital ID and amount', 'error');
        return;
    }

    try {
        const response = await fetch(`${API_URL}/request`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ hospitalId, amount })
        });

        const data = await response.json();

        if (data.success) {
            showNotification('Request submitted successfully', 'success');
            document.getElementById('requestHospitalId').value = '';
            document.getElementById('requestAmount').value = '';
            refreshData();
        } else {
            showNotification('Failed to submit request', 'error');
        }
    } catch (error) {
        console.error('Error submitting request:', error);
        showNotification('Error submitting request', 'error');
    }
}

// Quick request from hospital table
function quickRequest(hospitalId) {
    const amount = prompt(`Enter vaccine amount to request for Hospital ${hospitalId}:`, '500');
    if (amount && parseInt(amount) > 0) {
        document.getElementById('requestHospitalId').value = hospitalId;
        document.getElementById('requestAmount').value = amount;
        submitRequest();
    }
}

// Process allocation with selected algorithm
async function processAllocation() {
    const algorithm = document.getElementById('algorithmSelect').value;

    try {
        const response = await fetch(`${API_URL}/allocate`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ algorithm })
        });

        const data = await response.json();

        if (data.success) {
            showNotification(`Allocation processed using ${algorithm}`, 'success');
            refreshData();
        } else {
            showNotification('Failed to process allocation', 'error');
        }
    } catch (error) {
        console.error('Error processing allocation:', error);
        showNotification('Error processing allocation', 'error');
    }
}

// Replenish vaccines
async function replenishVaccines() {
    const amount = parseInt(document.getElementById('replenishAmount').value);

    if (!amount || amount <= 0) {
        showNotification('Please enter a valid amount', 'error');
        return;
    }

    try {
        const response = await fetch(`${API_URL}/replenish`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ amount })
        });

        const data = await response.json();

        if (data.success) {
            showNotification(`Added ${amount.toLocaleString()} vaccines to inventory`, 'success');
            refreshData();
        } else {
            showNotification('Failed to replenish vaccines', 'error');
        }
    } catch (error) {
        console.error('Error replenishing vaccines:', error);
        showNotification('Error replenishing vaccines', 'error');
    }
}

// Refresh all data
async function refreshData() {
    await fetchStatus();
    await fetchHospitals();
}

// Show notification (simple implementation)
function showNotification(message, type) {
    // Simple alert for now - can be enhanced with a toast notification library
    const prefix = type === 'success' ? '✓' : '✗';
    alert(`${prefix} ${message}`);
}

// Initialize on page load
document.addEventListener('DOMContentLoaded', () => {
    refreshData();

    // Auto-refresh every 5 seconds
    setInterval(refreshData, 5000);
});

// Handle Enter key in request form
document.addEventListener('keypress', (e) => {
    if (e.key === 'Enter') {
        const activeElement = document.activeElement;
        if (activeElement.id === 'requestHospitalId' || activeElement.id === 'requestAmount') {
            submitRequest();
        }
    }
});
