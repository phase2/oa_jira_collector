<?php

/**
 * @file
 * Defines the JIRA Issue Collector widget.
 */

$plugin = array(
  'title' => t('JIRA Issue Collector'),
  'description' => t('Display a button for adding an issue via the JIRA Issue Collector.'),
  'single' => TRUE,
  'category' => t('JIRA'),
  'edit form' => 'oa_jira_collector_widget_edit_form',
  'render callback' => 'oa_jira_collector_widget_render',
  'defaults' => array(
    'caption' => '',
    'collector' => '',
    'btn_classes' => '',
    'showbtn' => TRUE,
  ),
);


/**
 * Render callback for the widget.
 */
function oa_jira_collector_widget_render($subtype, $conf, $args, $context = NULL) {

  $collector = $conf['collector'];
  if (preg_match('#src="(.+?)"#', $collector, $matches) > 0) {
    $collector = $matches[1];
  }

  drupal_add_js(drupal_get_path('module', 'oa_jira_collector') . '/oa_jira_collector.js');
  drupal_add_js(array('oaJiraCollector' => array('url' => drupal_strip_dangerous_protocols($collector))), 'setting');

  if (!empty($conf['showbtn'])) {
    $block = new stdClass();
    $block->title = '';
    $vars['caption'] = !empty($conf['caption']) ? $conf['caption'] : t('Submit an issue');
    $vars['btn_classes'] = !empty($conf['btn_classes']) ? $conf['btn_classes'] : '';
    $block->content = theme('oa_jira_collector', $vars);
    return $block;
  }
  else {
    return FALSE;
  }
}

/**
 * Edit form for the panel.
 */
function oa_jira_collector_widget_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['collector'] = array(
    '#title' => t('Collector data'),
    '#description' => t('Paste the JIRA Collector code given from JIRA here.'),
    '#type' => 'textarea',
    '#default_value' => $conf['collector'],
  );
  $form['showbtn'] = array(
    '#title' => t('Show button'),
    '#type' => 'checkbox',
    '#default_value' => $conf['showbtn'],
  );
  $form['caption'] = array(
    '#title' => t('Button caption'),
    '#type' => 'textfield',
    '#default_value' => $conf['caption'],
    '#states' => array(
      'visible' => array(
        ':input[name="showbtn"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['btn_classes'] = array(
    '#title' => t('CSS Classes'),
    '#description' => t('Additional button Bootstrap classes, such as btn-primary'),
    '#type' => 'textfield',
    '#default_value' => $conf['btn_classes'],
    '#states' => array(
      'visible' => array(
        ':input[name="showbtn"]' => array('checked' => TRUE),
      ),
    ),
  );

  return $form;
}

/**
 * Submit handler for edit form. Save the custom form fields we added.
 */
function oa_jira_collector_widget_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

