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
  'edit form' => 'oa_jira_collector_edit_form',
  'render callback' => 'oa_jira_collector_render',
  'defaults' => array(
    'caption' => '',
    'collector' => '',
  ),
);


/**
 * Render callback for the widget.
 */
function oa_jira_collector_render($subtype, $conf, $args, $context = NULL) {

  $block = new stdClass();
  $block->title = '';
  $vars['collector'] = $conf['collector'];
  $vars['caption'] = !empty($conf['caption']) ? $conf['caption'] : t('Submit an issue');
  $block->content = theme('oa_jira_collector', $vars);

  return $block;
}

/**
 * Edit form for the panel.
 */
function oa_jira_collector_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['caption'] = array(
    '#title' => t('Button caption'),
    '#type' => 'textfield',
    '#default_value' => $conf['caption'],
  );
  $form['collector'] = array(
    '#title' => t('Collector data'),
    '#description' => t('Paste the JIRA Collector code given from JIRA here.'),
    '#type' => 'textarea',
    '#default_value' => $conf['collector'],
  );

  return $form;
}

/**
 * Submit handler for edit form. Save the custom form fields we added.
 */
function oa_jira_collector_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

