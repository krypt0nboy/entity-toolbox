<?php

/**
 * Class ParentEntityProperty
 */
class ParentEntityProperty extends EntityProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                => 'parent',
        'default_reference'           => '%reference_info_entity_type%',
        'default_name'                => '%reference_info_entity_type%',
        'default_drupal_type'         => '%reference_info_entity_type%',
        'default_label'               => '%reference_info_label%',
        'default_description'         => 'The %toolbox_info_entity_type% %reference_info_label% (parent).',
        'default_has_revisions'       => TRUE,
        'default_has_translations'    => FALSE,
        'default_key'                 => '%reference_info_entity_keys_id%',
        'default_schemas_fields_name' => array(
          'base'              => 'parent_%reference_info_entity_keys_id%',
          'revision'          => 'parent_%reference_info_entity_keys_id%',
          'relation'          => 'parent_%reference_info_entity_keys_id%',
          'relation_revision' => 'parent_%reference_info_entity_keys_id%',
        ),
        'default_schemas_fields'      => array(
          'base'     => array(
            'description' => 'The {%reference_info_base_table%}.%reference_info_entity_keys_id%.',
          ),
          'revision' => array(
            'description' => 'The {%reference_info_base_table%}.%reference_info_entity_keys_id% revision.',
          ),
        ),
        'default_forms'               => array(
          'edit'   => array(
            'required' => TRUE,
          ),
          'inline' => array(
            'expose' => TRUE,
          ),
        ),
      ),
      $args
    );

    parent::__construct($args);
  }
}