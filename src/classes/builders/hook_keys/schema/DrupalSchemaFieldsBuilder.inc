<?php

/**
 * Class DrupalSchemaFieldsBuilder
 */
class DrupalSchemaFieldsBuilder extends SchemaKeyBuilder {
  /**
   * @var array $requiredSchemaPropertyTypes
   *   The property types required for this schema type.
   */
  protected $requiredSchemaPropertyTypes = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'self_key'                       => 'fields',
      'required_schema_property_types' => array(
        'entity_id'          => TRUE,
        'entity_revision_id' => TRUE,
        'translation_set_id' => TRUE,
      )
    ), $args);
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function genDynamicStructure() {
    $fields             = $this->extractSchemaFields($this->schemaType);
    $structure          = array();
    $keyBuildersClasses = array();
    $keyBuildersArgs    = array();
    foreach ($fields as $fieldName => $fieldArgs) {
      $structure[$fieldName]          = array(
        'type'   => 'array',
        'method' => 'buildField'
      );
      $keyBuildersClasses[$fieldName] = $this->guessSchemaFieldBuilderClass($fieldArgs['property_name'], $this->schemaType);
      $keyBuildersArgs[$fieldName]    = $fieldArgs;
    }
    $this->__set('key_builders_classes', $keyBuildersClasses);
    $this->__set('key_builders_args', $keyBuildersArgs);

    return $structure;
  }

  /**
   * Guess a property schema field builder class.
   *
   * @param string $propertyName
   *   The property name.
   * @param string $schemaType
   *   The schema type.
   *
   * @return string
   */
  public function guessSchemaFieldBuilderClass($propertyName, $schemaType = NULL) {
    $schemaType = !isset($schemaType) ? $this->schemaType : $schemaType;
    $baseClass  = 'DrupalSchemaFieldBuilder';
    $modelClass = '%schema_type%' . $baseClass;
    $vars       = array(
      'schema_type' => $schemaType
    );
    $class      = string_template_process($modelClass, $vars);

    return class_exists($class) ? $class : $baseClass;
  }

  /**
   * Extracts and returns the schema fields and their args for builders.
   *
   * @param string $schemaType
   *   The schema type.
   *
   * @return array
   */
  protected function extractSchemaFields($schemaType = NULL) {
    $schemaType = !isset($schemaType) ? $this->schemaType : $schemaType;
    $fields     = array();
    foreach ($this->properties as $propertyName => $propertyInfo) {
      $extract = $this->evalExtractPropertyField($propertyName, $schemaType);
      if ($extract) {
        $fields[$this->extractSchemaFieldName($propertyName, $schemaType)] = $this->extractPropertySchemaFieldBuilderArgs($propertyName, $schemaType);
      }
    }

    return $fields;
  }

  /**
   * Evaluates if a property should be extracted as a field.
   *
   * @param string      $propertyName
   * @param null|string $schemaType
   *
   * @return bool
   */
  protected function evalExtractPropertyField($propertyName, $schemaType = NULL) {
    $schemaType = !isset($schemaType) ? $this->schemaType : $schemaType;
    $eval       = $this->evalExtractPropertyFieldMethods($propertyName, $schemaType);
    if (in_array(FALSE, $eval, TRUE)) {

      return FALSE;
    }
    elseif (in_array(TRUE, $eval, TRUE)) {

      return TRUE;
    }

    return FALSE;
  }

  /**
   * Evaluates methods for evalExtractPropertyField.
   *
   * @param string      $propertyName
   * @param null|string $schemaType
   *
   * @return array
   */
  protected function evalExtractPropertyFieldMethods($propertyName, $schemaType = NULL) {
    $eval              = array();
    $helper            = $this->getPropsHelper();
    $eval['multiple']  = !$helper->propIsMulti($propertyName) || $helper->propIsSerialized($propertyName);
    $eval['has_field'] = $helper->propHasSchemaFieldName($propertyName, $schemaType);

    return $eval;
  }

  /**
   * Evaluates if a property is multi.
   *
   * @param string $propertyName
   *   The property name.
   *
   * @return bool
   */
  public function isPropertyMultiple($propertyName) {
    return $this->properties[$propertyName]['multiple'];
  }

  /**
   * Evaluates if a property is the revision id property.
   *
   * @param string $propertyName
   *   The property name.
   *
   * @return bool
   */
  public function isRevisionProperty($propertyName) {
    return $this->properties[$propertyName]['entity_revision_id'];
  }

  /**
   * Evaluates if a property is the entity id property.
   *
   * @param string $propertyName
   *   The property name.
   *
   * @return bool
   */
  public function isEntityIdProperty($propertyName) {
    return $this->properties[$propertyName]['type'] == 'entity_id';
  }

  /**
   * Evaluates if a property is serialized.
   *
   * @param string $propertyName
   *   The property name.
   *
   * @return bool
   */
  public function isPropertySerialized($propertyName) {
    return $this->properties[$propertyName]['serialize'];
  }

  /**
   * Evaluates if a property is required for this schema type.
   *
   * @param string $propertyName
   *   The property name.
   *
   * @return bool
   */
  public function isRequiredSchemaProperty($propertyName) {
    $type = $this->properties[$propertyName]['type'];

    return in_array($type, array_keys($this->requiredSchemaPropertyTypes));
  }

  /**
   * Evaluates if a property has a schema field name.
   *
   * @param string $propertyName
   *   The property name.
   * @param string $schemaType
   *   The schema type.
   *
   * @return bool
   */
  public function propertyHasSchemaFieldName($propertyName, $schemaType = NULL) {
    $schemaType = !isset($schemaType) ? $this->schemaType : $schemaType;

    return !empty($this->properties[$propertyName]['schemas_fields_name'][$schemaType]);
  }

  /**
   * Extracts and returns a property schema field name.
   *
   * @param string $propertyName
   * @param string $schemaType
   *
   * @return string
   */
  protected function extractSchemaFieldName($propertyName, $schemaType = NULL) {
    $schemaType = !isset($schemaType) ? $this->schemaType : $schemaType;

    return $this->properties[$propertyName]['schemas_fields_name'][$schemaType];
  }

  /**
   * Extracts and returns a property schema field.
   *
   * @param string $propertyName
   * @param string $schemaType
   *
   * @return array
   */
  protected function extractPropertySchemaFieldBuilderArgs($propertyName, $schemaType = NULL) {
    $schemaType = !isset($schemaType) ? $this->schemaType : $schemaType;
    $args       = array(
      'property_name' => $propertyName,
      'property_type' => $this->properties[$propertyName]['type'],
    );

    return $args;
  }

  /** {{@inheritdoc}} */
  public function build() {
    $this->setPhase(self::PHZ__BUILD);
    $this->preBuild();
    foreach (array_keys($this->getStructure()) as $fieldName) {
      $this->setKeyBuild($fieldName, $this->buildField($fieldName));
    }
    $this->validateBuild();
    $this->postBuild();

    return $this->deliver();
  }

  /**
   * @param $fieldName
   * @return array
   */
  protected function buildField($fieldName) {
    return $this->getKeyBuilder($fieldName)->build();
  }

//  /**
//   * @return array
//   */
//  protected function buildRevisionField() {
//    return array(
//      'vid' => array(
//        'type'        => 'int',
//        'description' => $this->processValueTemplate('The current {%toolbox_info_tables_revision%}.%toolbox_info_keys_id% version identifier.'),
//        'unsigned'    => TRUE,
//        'not null'    => TRUE,
//      )
//    );
//  }

//  /**
//   * @return array
//   */
//  protected function buildTranslationSetField() {
//    $fieldName = $this->processValueTemplate('t%toolbox_info_entity_type%id');
//
//    return array(
//      $fieldName => array(
//        'description' => $this->processValueTemplate('The translation set id for this %toolbox_info_entity_type%, which equals the %toolbox_info_entity_type% id in each set.'),
//        'type'        => 'int',
//        'not null'    => TRUE,
//        'default'     => 0,
//      )
//    );
//  }

}