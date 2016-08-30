<?php

/**
 * Class EntityHumanNamePropertyFieldable
 */
class EntityHumanNamePropertyFieldable extends EntityHumanNameProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_key'                 => 'name',
        'default_label'               => '%toolbox_info_labels_single% name',
        'default_description'         => 'The name of this %toolbox_info_labels_single_lowercase% type.',
        'default_schemas_fields_name' => array(
          'base'     => 'name',
          'revision' => 'name',
        ),
        'default_schemas_fields'      => array(
          'base'      => array(
            'description' => 'The name of the %toolbox_info_entity_type% - a human-readable identifier.'
          ),
          'revisions' => array(
            'description' => 'A revision for {%entity_tables_base%}.%property_default_schemas_fields_name_base%.'
          ),
        ),
        'default_forms'               => array(
          'edit'  => array(
            'required' => TRUE
          ),
          'clone' => array(
            'required' => TRUE
          )
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}