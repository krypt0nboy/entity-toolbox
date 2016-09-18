<?php

/**
 * Class CreationTimeStampProperty
 */
class CreationTimeStampProperty extends TimeStampProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                => 'created',
        'default_name'                => 'created',
        'default_label'               => 'Created',
        'default_description'         => 'The UNIX timestamp when the %toolbox_info_labels_single_lowercase% was created.',
        'default_key'                 => 'created',
        'default_has_revisions'       => FALSE,
        'default_required'            => TRUE,
        'default_callbacks'           => array(
          'default' => 'request_time'
        ),
        'default_schemas_fields_name' => array(
          'base'     => 'created',
          'revision' => 'created',
        ),
        'default_schemas_fields'      => array(
          'base'     => array(
            'description' => 'The UNIX timestamp when the %toolbox_info_labels_single_lowercase% was created.',
          ),
          'revision' => array(
            'description' => 'The UNIX timestamp when the %toolbox_info_labels_single_lowercase% was created.',
          ),
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}